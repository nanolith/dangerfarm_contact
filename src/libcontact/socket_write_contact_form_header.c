#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_socket;

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
int DANGERFARM_CONTACT_SYM(socket_write_contact_form_header)(
    int s, const DANGERFARM_CONTACT_SYM(contact_form)* hdr)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_write_contact_form_header), s, hdr);

    int retval;

    /* write the name size. */
    retval = socket_write_uint64(s, hdr->name_size);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* write the email size. */
    retval = socket_write_uint64(s, hdr->email_size);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* write the subject size. */
    retval = socket_write_uint64(s, hdr->subject_size);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* write the comment size. */
    retval = socket_write_uint64(s, hdr->comment_size);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_write_contact_form_header), retval);

    return retval;
}
