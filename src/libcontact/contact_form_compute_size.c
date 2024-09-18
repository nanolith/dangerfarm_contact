#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

/**
 * \brief Given a valid \ref contact_form, compute the size.
 *
 * \param form          The contact form for this operation.
 *
 * \returns the size of this form.
 */
size_t DANGERFARM_CONTACT_SYM(contact_form_compute_size)(
    const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_compute_size), form);

    size_t retval =
        form->name_size + form->email_size + form->subject_size
      + form->comment_size + sizeof(*form);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_compute_size), retval);

    return retval;
}
