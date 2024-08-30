#include <dangerfarm_contact/status_codes.h>

#include "../../../src/contactdb/contactdb_internal.h"

int nondet_retval();

int contactdb_install_signal_handler(contactdb_context* ctx)
{
    int retval = nondet_retval();
    switch (retval)
    {
        case ERROR_CONTACTDB_SIGEMPTYSET_FAILURE:
        case ERROR_CONTACTDB_SIGACTION_FAILURE:
        case STATUS_SUCCESS:
            return retval;

        default:
            return ERROR_GENERAL_OUT_OF_MEMORY;
    }
}
