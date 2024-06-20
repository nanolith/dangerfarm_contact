#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>

#include "contactdb_internal.h"

/**
 * \brief Decode and dispatch a contactdb request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int contactdb_decode_and_dispatch(contactdb_context* ctx, int sock)
{
    int retval;
    uint32_t req;

    /* read the request id. */
    retval = database_read_request_id(&req, sock);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* decode the request id. */
    switch (req)
    {
        case DATABASE_REQUEST_ID_CONTACT_FORM_APPEND:
            retval = contactdb_dnd_contact_form_append(ctx, sock);
            break;

        case DATABASE_REQUEST_ID_CONTACT_FORM_GET_COUNT:
            retval = contactdb_dnd_contact_form_get_count(ctx, sock);
            break;

        case DATABASE_REQUEST_ID_CONTACT_FORM_GET_LIST:
            retval = contactdb_dnd_contact_form_get_list(ctx, sock);
            break;

        default:
            retval =
                database_write_generic_response(
                    sock, req, ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID);
            break;
    }

done:
    return retval;
}
