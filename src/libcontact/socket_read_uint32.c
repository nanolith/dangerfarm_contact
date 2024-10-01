#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <unistd.h>

/**
 * \brief Read a uint32_t value from a socket.
 *
 * \param val           Pointer to the value to read.
 * \param s             The socket from which the value is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_read_uint32)(uint32_t* val, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_uint32), val, s);

    int retval;
    ssize_t read_bytes = 0;

    /* read the value. */
    read_bytes = read(s, val, sizeof(*val));
    if (read_bytes < 0 || (size_t)read_bytes != sizeof(*val))
    {
        *val = 0;
        retval = ERROR_SOCKET_READ;
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_uint32), retval, val);

    return retval;
}
