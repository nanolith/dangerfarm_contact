#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/util/string.h>

/**
 * \brief Given a \ref contact_form, extract the comment as a string.
 *
 * \note This string is owned by the caller and must be reclaimed using \ref
 * string_release.
 *
 * \param comment       Pointer to the char pointer to receive the comment on
 *                      success.
 * \param form          The \ref contact_form instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contact_form_extract_comment(char** comment, const contact_form* form)
{
    size_t offset = form->name_size + form->email_size;

    return string_create(comment, form->data + offset, form->comment_size);
}
