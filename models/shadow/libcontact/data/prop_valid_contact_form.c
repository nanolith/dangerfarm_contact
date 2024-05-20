#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

bool prop_valid_contact_form(const contact_form* form)
{
    size_t size = contact_form_compute_size(form);
    size_t data_size = size - sizeof(*form);

    MODEL_ASSERT(STATUS_SUCCESS == contact_form_verify(form, size));
    MODEL_ASSERT(form->data[0] == form->data[0]);
    MODEL_ASSERT(form->data[data_size - 1] == form->data[data_size - 1]);

    return true;
}
