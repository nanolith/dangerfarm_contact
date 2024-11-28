#include <dangerfarm_contact/status_codes.h>

#include "../../../src/contactdb/contactdb_internal.h"

int nondet_retval();

int contactdb_drop_privileges(contactdb_context* ctx)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_drop_privileges, ctx);

    int retval = nondet_retval();

    switch (retval)
    {
        case STATUS_SUCCESS:
            retval = STATUS_SUCCESS;
            goto done;

        case ERROR_CONTACTDB_DROP_PRIVILEGES:
        default:
            retval = ERROR_CONTACTDB_DROP_PRIVILEGES;
            goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(contactdb_drop_privileges, retval);

    return retval;
}
