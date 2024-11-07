#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

int DANGERFARM_CONTACT_SYM(database_read_contact_form_append_request_payload)(
    DANGERFARM_CONTACT_SYM(contact_form)** form, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_append_request_payload),
        form, s);

    int retval = contact_form_create_nondet(form);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_append_request_payload),
        retval, form);

    return retval;
}
