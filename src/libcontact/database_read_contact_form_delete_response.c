#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Read a contact delete response from the socket.
 *
 * \param status    The status for this request.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_delete_response)(
    uint32_t* status, int s)
{
    int retval;
    uint32_t request_id;

    /* read the request id. */
    retval = socket_read_uint32(&request_id, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* verify the request id. */
    if (DATABASE_REQUEST_ID_CONTACT_FORM_DELETE != request_id)
    {
        return ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID;
    }

    /* read the status. */
    retval = socket_read_uint32(status, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
