#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

/**
 * \brief Decode and dispatch a contactdb contact form get count request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int contactdb_dnd_contact_form_get_count(contactdb_context* ctx, int sock)
{
    int retval;
    uint64_t count = 0;
    MDB_txn* txn = NULL;

    /* is this socket allowed to perform this operation? */
    if (
        !contactdb_has_capability(
            ctx, DATABASE_CAPABILITY_CONTACT_FORM_COUNT_GET))
    {
        retval = ERROR_CONTACTDB_PERMISSION_DENIED;
        goto write_response;
    }

    /* create a read-only transaction. */
    retval = mdb_txn_begin(ctx->conn->env, NULL, MDB_RDONLY, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_TXN_BEGIN;
        goto write_response;
    }

    /* Get the total count. */
    retval =
        contactdb_connection_counter_get(
            ctx->conn, txn, COUNTER_ID_CONTACT_COUNT, &count);
    if (STATUS_SUCCESS != retval)
    {
        goto rollback_txn;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto rollback_txn;

rollback_txn:
    if (NULL != txn)
    {
        mdb_txn_abort(txn);
        txn = NULL;
    }

write_response:
    return database_write_contact_form_get_count_response(sock, retval, count);
}
