#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <unistd.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Write a list contact forms response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this response.
 * \param count     The count of the id list.
 * \param id_list   The id list to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_list_response)(
    int s, const uint32_t status, const uint64_t count,
    const uint64_t* id_list)
{
    int retval;
    ssize_t wrote_bytes;

    /* write the request id. */
    retval = socket_write_uint32(s, DATABASE_REQUEST_ID_CONTACT_FORM_GET_LIST);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the status. */
    retval = socket_write_uint32(s, status);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* continue only if the status is successful. */
    if (STATUS_SUCCESS != status)
    {
        return STATUS_SUCCESS;
    }

    /* write the count. */
    retval = socket_write_uint64(s, count);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the id list. */
    size_t length = count * sizeof(uint64_t);
    wrote_bytes = write(s, id_list, count * sizeof(uint64_t));
    if (wrote_bytes < 0 || (size_t)wrote_bytes != length)
    {
        return ERROR_SOCKET_WRITE;
    }

    /* success. */
    return STATUS_SUCCESS;
}
