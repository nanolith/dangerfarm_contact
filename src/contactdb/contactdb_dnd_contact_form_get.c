#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

/**
 * \brief Decode and dispatch a contactdb contact form get request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int contactdb_dnd_contact_form_get(contactdb_context* ctx, int sock)
{
    int retval;
    bool response_written = false;
    const contact_form* form = NULL;
    MDB_txn* txn = NULL;
    uint64_t id = 0;

    /* is this socket allowed to perform this operation? */
    if (!contactdb_has_capability(ctx, DATABASE_CAPABILITY_CONTACT_FORM_GET))
    {
        retval = ERROR_CONTACTDB_PERMISSION_DENIED;
        goto write_response;
    }

    /* read the request payload. */
    retval = database_read_contact_form_read_request_payload(&id, sock);
    if (STATUS_SUCCESS != retval)
    {
        goto write_response;
    }

    /* create a read-only transaction. */
    retval = mdb_txn_begin(ctx->conn->env, NULL, MDB_RDONLY, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_TXN_BEGIN;
        goto write_response;
    }

    /* get the form. */
    retval = contactdb_connection_form_get(ctx->conn, txn, id, &form);
    if (STATUS_SUCCESS != retval)
    {
        goto rollback_txn;
    }

    /* write the response. */
    retval = database_write_contact_form_read_response(sock, retval, form);
    goto rollback_txn;

rollback_txn:
    if (NULL != txn)
    {
        mdb_txn_abort(txn);
        txn = NULL;
    }

write_response:
    if (!response_written)
    {
        retval = database_write_contact_form_read_response(sock, retval, form);
    }

    return retval;
}
