#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(database_write_database_truncate_response)(
    int s, const uint32_t status)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_database_truncate_response), s,
        status);

    int retval = nondet_retval();

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_database_truncate_response),
        retval);

    return retval;
}
