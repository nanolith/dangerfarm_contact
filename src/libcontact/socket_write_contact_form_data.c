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
int DANGERFARM_CONTACT_SYM(socket_write_contact_form_data)(
    int s, const char* data, size_t size)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_write_contact_form_data), s, data, size);

    int retval;
    ssize_t wrote_bytes = 0;

    /* write the data. */
    wrote_bytes = write(s, data, size);
    if (wrote_bytes < 0 || (size_t)wrote_bytes != size)
    {
        retval = ERROR_SOCKET_WRITE;
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_write_contact_form_data), retval);

    return retval;
}
