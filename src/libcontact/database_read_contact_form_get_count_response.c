#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Read a contact form get count response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param count     Pointer to receive the count on success.
 * \param s         The socket from which this response is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_get_count_response)(
    uint32_t* status, uint64_t* count, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_get_count_response),
        status, count, s);

    int retval;
    uint32_t request_id;

    /* read the request id. */
    retval = socket_read_uint32(&request_id, s);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* verify the request id. */
    if (DATABASE_REQUEST_ID_CONTACT_FORM_GET_COUNT != request_id)
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

    /* verify the status. */
    if (STATUS_SUCCESS != *status)
    {
        /* status can't be invalid if the API response is well formed. */
        if (ERROR_INVALID_STATUS == *status)
        {
            retval = ERROR_INVALID_STATUS;
            goto fail;
        }
        /* if the remote status is a valid failure, this is up to the caller to
         * determine. */
        else
        {
            *count = 0;
            retval = STATUS_SUCCESS;
        }

        goto done;
    }

    /* read the count. */
    retval = socket_read_uint64(count, s);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *status = ERROR_INVALID_STATUS;
    *count = 0;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_get_count_response),
        retval, status, count);

    return retval;
}
