#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Read a database truncate response from the socket.
 *
 * \param status    The status for this response.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_database_truncate_response)(
    uint32_t* status, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_database_truncate_response),
        status, s);

    int retval;
    uint32_t request_id;

    /* read the request id. */
    retval = socket_read_uint32(&request_id, s);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* verify the request id. */
    if (DATABASE_REQUEST_ID_TRUNCATE != request_id)
    {
        retval = ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID;
        goto fail;
    }

    /* read the status. */
    retval = socket_read_uint32(status, s);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* if the status is invalid, then fail. */
    if (ERROR_INVALID_STATUS == *status)
    {
        retval = ERROR_INVALID_STATUS;
        goto fail;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *status = ERROR_INVALID_STATUS;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_database_truncate_response),
        retval, status);

    return retval;
}
