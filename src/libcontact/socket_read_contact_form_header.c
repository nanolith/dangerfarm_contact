#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Read a contact form header from a socket.
 *
 * \note This reads the size data for the contact form, into a stack allocated
 * contact form header. The resulting form should NOT be released.
 *
 * \param hdr           Pointer to the \ref contact_form header to read.
 * \param s             The socket from which the value is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_read_contact_form_header)(
    DANGERFARM_CONTACT_SYM(contact_form)* hdr, int s)
{
    int retval;

    /* read the name size. */
    retval = socket_read_uint64(&hdr->name_size, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* read the email size. */
    retval = socket_read_uint64(&hdr->email_size, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* read the subject size. */
    retval = socket_read_uint64(&hdr->subject_size, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* read the comment size. */
    retval = socket_read_uint64(&hdr->comment_size, s);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
