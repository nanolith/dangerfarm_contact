#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

/**
 * \brief Write a contact form header to a socket.
 *
 *
 * \param s             The socket to which the value is written.
 * \param hdr           Pointer to the \ref contact_form header to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int socket_write_contact_form_header(int s, const contact_form* hdr)
{
    int retval;

    /* write the name size. */
    retval = socket_write_uint64(s, hdr->name_size);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the email size. */
    retval = socket_write_uint64(s, hdr->email_size);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the subject size. */
    retval = socket_write_uint64(s, hdr->subject_size);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the comment size. */
    retval = socket_write_uint64(s, hdr->comment_size);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
