#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

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
    MDB_val key, val;
    uint64_t count, contact_id;

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

    /* Get the total count. */
    retval =
        contactdb_connection_counter_get(
            ctx->conn, txn, COUNTER_ID_CONTACT_COUNT, &count);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_form;
    }

    /* verify total count. */
    if (count >= DATABASE_PROTOCOL_MAX_COUNT)
    {
        retval = ERROR_CONTACTDB_FULL;
        goto cleanup_form;
    }

    /* get a unique contact id. */
    retval =
        contactdb_connection_counter_get_and_increment(
            ctx->conn, txn, COUNTER_ID_CONTACT_KEY, &contact_id);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_form;
    }

    /* set up the payload for this transaction. */
    key.mv_size = sizeof(contact_id);
    key.mv_data = &contact_id;
    val.mv_size = contact_form_compute_size(form);
    val.mv_data = form;

    /* put this value into the database. */
    retval = mdb_put(txn, ctx->conn->contact_db, &key, &val, 0);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_PUT;
        goto rollback_txn;
    }

    /* increment the count. */
    retval =
        contactdb_connection_counter_get_and_increment(
            ctx->conn, txn, COUNTER_ID_CONTACT_COUNT, &count);
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
