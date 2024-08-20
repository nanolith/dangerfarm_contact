#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Write a contact read response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this response.
 * \param form      The contact form to write to the socket.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_read_response)(
    int s, const uint32_t status,
    const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    int retval;

    /* write the request id. */
    retval = socket_write_uint32(s, DATABASE_REQUEST_ID_CONTACT_FORM_GET);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the status. */
    retval = socket_write_uint32(s, status);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* skip the contact form payload if the status was not successful. */
    if (STATUS_SUCCESS != status)
    {
        return STATUS_SUCCESS;
    }

    /* write the contact form data. */
    retval = contact_form_write(s, form);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
