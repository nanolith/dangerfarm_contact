#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <unistd.h>

/**
 * \brief Write contact form data to a socket.
 *
 * \param s             The socket to which this data is written.
 * \param data          Pointer to the data buffer to write.
 * \param size          The size of the data to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int socket_write_contact_form_data(int s, const char* data, size_t size)
{
    ssize_t wrote_bytes = 0;

    /* write the data. */
    wrote_bytes = write(s, data, size);
    if (wrote_bytes < 0 || (size_t)wrote_bytes != size)
    {
        return ERROR_SOCKET_WRITE;
    }

    return STATUS_SUCCESS;
}
