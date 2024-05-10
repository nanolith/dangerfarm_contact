#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/util/string.h>

/**
 * \brief Given a \ref contact_form, extract the name as a string.
 *
 * \note This string is owned by the caller and must be reclaimed using \ref
 * string_release.
 *
 * \param name          Pointer to the char pointer to receive the name on
 *                      success.
 * \param form          The \ref contact_form instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contact_form_extract_name(char** name, const contact_form* form)
{
    size_t offset = 0;

    return string_create(name, form->data + offset, form->name_size);
}
