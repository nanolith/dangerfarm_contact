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
size_t contact_form_compute_size(const contact_form* form)
{
    return
        form->name_size + form->email_size + form->subject_size
      + form->comment_size + sizeof(*form);
}
