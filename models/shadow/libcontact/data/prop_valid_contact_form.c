#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

bool DANGERFARM_CONTACT_SYM(prop_valid_contact_form)(
    const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    size_t size = contact_form_compute_size(form);
    size_t data_size = size - sizeof(*form);

    MODEL_ASSERT(STATUS_SUCCESS == contact_form_verify(form, size));
    if (data_size > 0)
    {
        MODEL_CHECK_OBJECT_READ(form->data, data_size);
    }

    return true;
}
