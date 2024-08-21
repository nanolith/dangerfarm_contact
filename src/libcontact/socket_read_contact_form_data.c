#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <unistd.h>

/**
 * \brief Read contact form data from a socket.
 *
 * \note This read assumes that the backing buffer was already allocated by the
 * caller. This convenience method just makes model checking easier.
 *
 * \param data          Pointer to the data buffer to be populated by this read.
 * \param s             The socket from which this data is read.
 * \param size          The size of the data to read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_read_contact_form_data)(
    char* data, int s, size_t size)
{
    ssize_t read_bytes = 0;

    /* read the data. */
    read_bytes = read(s, data, size);
    if (read_bytes < 0 || (size_t)read_bytes != size)
    {
        return ERROR_SOCKET_READ;
    }

    return STATUS_SUCCESS;
}
