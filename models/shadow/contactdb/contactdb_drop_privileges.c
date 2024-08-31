#include <dangerfarm_contact/status_codes.h>

#include "../../../src/contactdb/contactdb_internal.h"

int nondet_retval();

int contactdb_drop_privileges(contactdb_context* ctx)
{
    int retval = nondet_retval();

    switch (retval)
    {
        case STATUS_SUCCESS:
            return STATUS_SUCCESS;

        case ERROR_CONTACTDB_DROP_PRIVILEGES:
            return ERROR_CONTACTDB_DROP_PRIVILEGES;

        default:
            return ERROR_CONTACTDB_DROP_PRIVILEGES;
    }
}
