#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <unistd.h>

/**
 * \brief Write a uint32_t value to a socket.
 *
 * \param s             The socket to which the value is written.
 * \param val           The value to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int socket_write_uint32(int s, uint32_t val)
{
    ssize_t wrote_bytes = 0;

    /* write the value. */
    wrote_bytes = write(s, &val, sizeof(val));
    if (wrote_bytes < 0 || (size_t)wrote_bytes != sizeof(val))
    {
        return ERROR_SOCKET_WRITE;
    }

    return STATUS_SUCCESS;
}
