#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <unistd.h>

/**
 * \brief Write a \ref contact_form to the given descriptor.
 *
 * \param s             The descriptor to which the \ref contact_form is
 *                      written.
 * \param form          The \ref contact_form to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contact_form_write(int s, const contact_form* form)
{
    ssize_t wrote_bytes = 0;
    size_t size = contact_form_compute_size(form);

    /* write the size bytes. */
    wrote_bytes = write(s, &size, sizeof(size));
    if (wrote_bytes < 0 || (size_t)wrote_bytes != sizeof(size))
    {
        return ERROR_CONTACT_FORM_WRITE;
    }

    /* write the contact form. */
    wrote_bytes = write(s, form, size);
    if (wrote_bytes < 0 || (size_t)wrote_bytes != size)
    {
        return ERROR_CONTACT_FORM_WRITE;
    }

    /* success. */
    return STATUS_SUCCESS;
}
