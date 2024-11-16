#include <dangerfarm_contact/data/contact_form.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(database_write_contact_form_read_response)(
    int s, const uint32_t status,
    const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_read_response),
        s, status, form);

    int retval = nondet_retval();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_read_response),
        retval);

    return retval;
}
