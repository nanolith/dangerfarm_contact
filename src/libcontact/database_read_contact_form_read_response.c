#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

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
int database_read_contact_form_read_response(
    uint32_t* status, contact_form** form, int s)
{
    int retval;
    uint32_t request_id;

    /* read the request id. */
    retval = socket_read_uint32(&request_id, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* verify that the request id matches what we expect. */
    if (DATABASE_REQUEST_ID_CONTACT_FORM_GET != request_id)
    {
        return ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID;
    }

    /* read the status. */
    retval = socket_read_uint32(status, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* only read the payload if the status is successful. */
    if (STATUS_SUCCESS != *status)
    {
        return STATUS_SUCCESS;
    }

    /* read the contact form data. */
    return contact_form_read(form, s);
}
