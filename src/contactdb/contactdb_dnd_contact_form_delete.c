#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

/**
 * \brief Decode and dispatch a contactdb contact form delete request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int contactdb_dnd_contact_form_delete(contactdb_context* ctx, int sock)
{
    int retval;
    MDB_txn* txn = NULL;
    MDB_val key;
    uint64_t count, id = 0;

    /* is this socket allowed to perform this operation? */
    if (!contactdb_has_capability(ctx, DATABASE_CAPABILITY_CONTACT_FORM_DELETE))
    {
        retval = ERROR_CONTACTDB_PERMISSION_DENIED;
        goto write_response;
    }

    /* read the request payload. */
    retval = database_read_contact_form_delete_request_payload(&id, sock);
    if (STATUS_SUCCESS != retval)
    {
        goto write_response;
    }

    /* create a transaction. */
    retval = mdb_txn_begin(ctx->conn->env, NULL, 0, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_TXN_BEGIN;
        goto write_response;
    }

    /* set up the key for the get request. */
    key.mv_size = sizeof(id);
    key.mv_data = &id;

    /* delete this entry from the database. */
    retval = mdb_del(txn, ctx->conn->contact_db, &key, NULL);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_DELETE;
        goto rollback_txn;
    }

    /* decrement the count. */
    retval =
        contactdb_connection_counter_get_and_decrement(
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
    txn = NULL;

    /* success. */
    retval = STATUS_SUCCESS;
    goto write_response;

rollback_txn:
    if (NULL != txn)
    {
        mdb_txn_abort(txn);
        txn = NULL;
    }

write_response:
    return database_write_contact_form_delete_response(sock, retval);
}
