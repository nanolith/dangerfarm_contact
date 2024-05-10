#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/util/string.h>

/**
 * \brief Given a \ref contact_form, extract the email as a string.
 *
 * \note This string is owned by the caller and must be reclaimed using \ref
 * string_release.
 *
 * \param email         Pointer to the char pointer to receive the email on
 *                      success.
 * \param form          The \ref contact_form instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contact_form_extract_email(char** email, const contact_form* form)
{
    size_t offset = form->name_size;

    return string_create(email, form->data + offset, form->email_size);
}
