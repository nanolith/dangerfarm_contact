#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Write a generic response to the socket.
 *
 * \param s         The socket from which this request is read.
 * \param req       The request id for this response.
 * \param status    The status for this response.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_generic_response)(
    int s, uint32_t req, uint32_t status)
{
    int retval;

    /* write the request id. */
    retval = socket_write_uint32(s, req);
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
