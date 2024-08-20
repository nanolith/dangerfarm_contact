#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Write a database truncate response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this response.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_database_truncate_response)(
    int s, const uint32_t status)
{
    int retval;

    /* write the request id. */
    retval = socket_write_uint32(s, DATABASE_REQUEST_ID_TRUNCATE);
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
