#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

/**
 * \brief Write a contact form append response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_write_contact_form_append_response(
    int s, const uint32_t status)
{
    int retval;

    /* write the request id. */
    retval = socket_write_uint32(s, DATABASE_REQUEST_ID_CONTACT_FORM_APPEND);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the status code. */
    retval = socket_write_uint32(s, status);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
