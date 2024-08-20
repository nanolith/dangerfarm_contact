#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Read a contact form get count response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param count     Pointer to receive the count on success.
 * \param s         The socket from which this response is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_get_count_response)(
    uint32_t* status, uint64_t* count, int s)
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
    if (DATABASE_REQUEST_ID_CONTACT_FORM_GET_COUNT != request_id)
    {
        return ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID;
    }

    /* read the status. */
    retval = socket_read_uint32(status, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* verify the status. */
    if (STATUS_SUCCESS != *status)
    {
        /* if the remote status is a failure, this is up to the caller to
         * determine. */
        return STATUS_SUCCESS;
    }

    /* read the count. */
    retval = socket_read_uint64(count, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
