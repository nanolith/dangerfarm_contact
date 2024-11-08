#include <dangerfarm_contact/protocol/database.h>

int nondet_status();

int DANGERFARM_CONTACT_SYM(database_write_contact_form_append_response)(
    int s, const uint32_t status)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_append_response),
        s, status);

    int retval = nondet_status();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_append_response),
        retval);

    return retval;
}
