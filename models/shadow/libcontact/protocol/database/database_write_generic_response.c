#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(database_write_generic_response)(
    int s, uint32_t req, uint32_t status)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_generic_response),
        s, req, status);

    int retval = nondet_retval();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_generic_response), retval);

    return retval;
}
