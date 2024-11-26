#include <dangerfarm_contact/status_codes.h>

#include "../../../src/contactdb/contactdb_internal.h"

int contactdb_disable_signal_handler(contactdb_context* ctx)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_disable_signal_handler, ctx);

    int retval = STATUS_SUCCESS;

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_disable_signal_handler, retval);

    return retval;
}
