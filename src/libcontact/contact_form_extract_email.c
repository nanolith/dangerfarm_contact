#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/util/string.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_string;

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
int DANGERFARM_CONTACT_SYM(contact_form_extract_email)(
    char** email, const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_extract_email), email, form);

    int retval;
    size_t offset = form->name_size;

    retval = string_create(email, form->data + offset, form->email_size);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_extract_email), retval, email);

    return retval;
}
