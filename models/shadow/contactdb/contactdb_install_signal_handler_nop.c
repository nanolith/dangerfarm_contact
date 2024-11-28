#include <dangerfarm_contact/status_codes.h>

#include "../../../src/contactdb/contactdb_internal.h"

int nondet_retval();

int contactdb_install_signal_handler(contactdb_context* ctx)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_install_signal_handler, ctx);

    int retval = nondet_retval();
    switch (retval)
    {
        case ERROR_CONTACTDB_SIGEMPTYSET_FAILURE:
        case ERROR_CONTACTDB_SIGACTION_FAILURE:
        case STATUS_SUCCESS:
            goto done;

        default:
            retval = ERROR_GENERAL_OUT_OF_MEMORY;
            goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_install_signal_handler, retval);

    return retval;
}
