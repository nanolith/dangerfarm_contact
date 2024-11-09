#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(database_write_contact_form_get_count_request)(
    int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_get_count_request),
        s);

    int retval =
        nondet_retval();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_get_count_request),
        retval);

    return retval;
}
