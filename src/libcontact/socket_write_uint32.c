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
int DANGERFARM_CONTACT_SYM(socket_write_uint32)(int s, uint32_t val)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_write_uint32), s, val);

    int retval;
    ssize_t wrote_bytes = 0;

    /* write the value. */
    wrote_bytes = write(s, &val, sizeof(val));
    if (wrote_bytes < 0 || (size_t)wrote_bytes != sizeof(val))
    {
        retval = ERROR_SOCKET_WRITE;
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_write_uint32), retval);

    return retval;
}
