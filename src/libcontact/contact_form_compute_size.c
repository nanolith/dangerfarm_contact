#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>

/**
 * \brief Given a valid \ref contact_form, compute the size.
 *
 * \param size          Pointer to receive the size on success.
 * \param form          The contact form for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contact_form_compute_size(size_t* size, const contact_form* form)
{
    *size =
        form->name_size + form->email_size + form->comment_size + sizeof(*form);

    return STATUS_SUCCESS;
}
