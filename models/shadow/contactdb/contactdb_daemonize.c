#include <dangerfarm_contact/status_codes.h>

#include "../../../src/contactdb/contactdb_internal.h"

int nondet_retval();

int contactdb_daemonize(contactdb_context* ctx)
{
    int retval = nondet_retval();

    switch (retval)
    {
        case ERROR_CONTACTDB_FORK:
        case ERROR_CONTACTDB_FORK_PARENT:
        case ERROR_CONTACTDB_SETSID:
        case STATUS_SUCCESS:
            return retval;

        default:
            return ERROR_CONTACTDB_FORK;
    }
}
