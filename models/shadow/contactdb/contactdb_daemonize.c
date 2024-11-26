#include <dangerfarm_contact/status_codes.h>

#include "../../../src/contactdb/contactdb_internal.h"

int nondet_retval();

int contactdb_daemonize(contactdb_context* ctx)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_daemonize, ctx);

    int retval = nondet_retval();

    switch (retval)
    {
        case ERROR_CONTACTDB_FORK:
        case ERROR_CONTACTDB_FORK_PARENT:
        case ERROR_CONTACTDB_SETSID:
        case STATUS_SUCCESS:
            goto done;

        default:
            retval = ERROR_CONTACTDB_FORK;
            goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(contactdb_daemonize, retval);

    return retval;
}
