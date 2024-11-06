#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(database_write_contact_form_append_request)(
    int s, const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_append_request),
        s, form);

    int retval = nondet_retval();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_append_request),
        retval);

    return retval;
}
