#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Read a contact form append response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param s         The socket from which this response is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_append_response)(
    uint32_t* status, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_append_response),
        status, s);

    int retval;
    uint32_t request_id;

    /* read the request id. */
    retval = socket_read_uint32(&request_id, s);
    if (STATUS_SUCCESS != retval)
    {
        *status = ERROR_INVALID_STATUS;
        goto done;
    }

    /* verify the request id. */
    if (DATABASE_REQUEST_ID_CONTACT_FORM_APPEND != request_id)
    {
        *status = ERROR_INVALID_STATUS;
        retval = ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID;
        goto done;
    }

    /* read the status. */
    retval = socket_read_uint32(status, s);
    if (STATUS_SUCCESS != retval)
    {
        *status = ERROR_INVALID_STATUS;
        goto done;
    }

    /* status can't be invalid if the API response is well formed. */
    if (ERROR_INVALID_STATUS == *status)
    {
        retval = ERROR_INVALID_STATUS;
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_append_response),
        retval, status);

    return retval;
}
