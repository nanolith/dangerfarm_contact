#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(database_write_database_truncate_request)(int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_database_truncate_request), s);

    /* generate a nondeterministic return value. */
    int retval = nondet_retval();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_database_truncate_request),
        retval);

    return retval;
}
