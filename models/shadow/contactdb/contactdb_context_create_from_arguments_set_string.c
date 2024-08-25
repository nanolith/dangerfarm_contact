#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "../../../src/contactdb/contactdb_context_create_from_arguments_internal.h"

int nondet_retval();

int contactdb_context_create_from_arguments_set_string(
    char** str, const char* opt, const char* value)
{
    int retval = nondet_retval();

    switch (retval)
    {
        case ERROR_CONTACTDB_BAD_PARAMETER:
        case ERROR_GENERAL_OUT_OF_MEMORY:
            return retval;

        default:
            retval = ERROR_CONTACTDB_BAD_PARAMETER;
            return retval;

        case STATUS_SUCCESS:
            if (NULL != *str)
            {
                *str = strdup(value);
                if (NULL == *str)
                    return ERROR_GENERAL_OUT_OF_MEMORY;
                return STATUS_SUCCESS;
            }
            else
            {
                return ERROR_CONTACTDB_BAD_PARAMETER;
            }
    }
}
