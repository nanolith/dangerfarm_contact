#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Read a contact read response from the socket.
 *
 * \note The form pointer is populated only if this function returns success AND
 * the status is set to success.
 *
 * \param status    The status for this response.
 * \param form      Pointer to the form pointer to get a created form instance
 *                  on success.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_read_response)(
    uint32_t* status, DANGERFARM_CONTACT_SYM(contact_form)** form, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_read_response),
        status, form, s);

    int retval;
    uint32_t request_id;

    /* read the request id. */
    retval = socket_read_uint32(&request_id, s);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* verify that the request id matches what we expect. */
    if (DATABASE_REQUEST_ID_CONTACT_FORM_GET != request_id)
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

    /* if the status is ERROR_INVALID_STATUS, then this is an error. */
    if (ERROR_INVALID_STATUS == *status)
    {
        retval = ERROR_INVALID_STATUS;
        goto fail;
    }

    /* only read the payload if the status is successful. */
    if (STATUS_SUCCESS != *status)
    {
        goto clear_form;
    }

    /* read the contact form data. */
    retval = contact_form_read(form, s);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *status = ERROR_INVALID_STATUS;

clear_form:
    *form = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_read_response),
        retval, status, form);

    return retval;
}
