#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Write a contact form get count response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status code to write.
 * \param count     The count to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_get_count_response)(
    int s, const uint32_t status, const uint64_t count)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_get_count_response),
        s, status, count);

    int retval;

    /* write the request id. */
    retval = socket_write_uint32(s, DATABASE_REQUEST_ID_CONTACT_FORM_GET_COUNT);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* write the status. */
    retval = socket_write_uint32(s, status);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* if the status is not success, then we are done. */
    if (STATUS_SUCCESS != status)
    {
        retval = STATUS_SUCCESS;
        goto done;
    }

    /* write the count. */
    retval = socket_write_uint64(s, count);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_get_count_response),
        retval);

    return retval;
}
