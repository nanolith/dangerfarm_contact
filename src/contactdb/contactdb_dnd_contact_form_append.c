#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

/* forward decls. */
static int verify_max_count(contactdb_context* ctx, MDB_txn* txn);

/**
 * \brief Decode and dispatch a contactdb contact form append request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int contactdb_dnd_contact_form_append(contactdb_context* ctx, int sock)
{
    int retval, release_retval;
    contact_form* form = NULL;
    MDB_txn* txn = NULL;

    /* is this socket allowed to perform this operation? */
    if (!contactdb_has_capability(ctx, DATABASE_CAPABILITY_CONTACT_FORM_APPEND))
    {
        retval = ERROR_CONTACTDB_PERMISSION_DENIED;
        goto write_response;
    }

    /* read a contact form request payload. */
    retval = database_read_contact_form_append_request_payload(&form, sock);
    if (STATUS_SUCCESS != retval)
    {
        goto write_response;
    }

    /* create a transaction. */
    retval = mdb_txn_begin(ctx->conn->env, NULL, 0, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_TXN_BEGIN;
        goto cleanup_form;
    }

    /* verify that appending a record won't exceed max count. */
    retval = verify_max_count(ctx, txn);
    if (STATUS_SUCCESS != retval)
    {
        goto rollback_txn;
    }

    /* append this form to the database. */
    retval = contactdb_connection_form_append(ctx->conn, txn, form);
    if (STATUS_SUCCESS != retval)
    {
        goto rollback_txn;
    }

    /* commit this transaction. */
    retval = mdb_txn_commit(txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_TXN_COMMIT;
        goto rollback_txn;
    }
    txn = NULL;

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_form;

rollback_txn:
    if (NULL != txn)
    {
        mdb_txn_abort(txn);
        txn = NULL;
    }

cleanup_form:
    release_retval = contact_form_release(form);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

write_response:
    return database_write_contact_form_append_response(sock, retval);
}

/**
 * \brief Verify the max count, returning an error if we can't append without
 * exceeding this count.
 *
 * \param ctx           The context for this operation.
 * \param txn           The database transaction for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int verify_max_count(contactdb_context* ctx, MDB_txn* txn)
{
    int retval;
    uint64_t count = 0;

    /* Get the total count. */
    retval =
        contactdb_connection_counter_get(
            ctx->conn, txn, COUNTER_ID_CONTACT_COUNT, &count);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* verify total count. */
    if (count >= DATABASE_PROTOCOL_MAX_COUNT)
    {
        return ERROR_CONTACTDB_FULL;
    }

    return STATUS_SUCCESS;
}
