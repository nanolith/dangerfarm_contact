#include <dangerfarm_contact/status_codes.h>

#include "../../../src/contactdb/contactdb_context_create_from_arguments_internal.h"

int nondet_retval();

int contactdb_context_create_from_arguments_bind_local_socket(
    contactdb_context* ctx)
{
    int retval = nondet_retval();

    switch (retval)
    {
        case ERROR_CONTACTDB_SOCKET_PATH_TOO_LONG:
        case ERROR_CONTACTDB_SOCKET_FAILURE:
        case ERROR_CONTACTDB_UNLINK_FAILURE:
        case ERROR_CONTACTDB_BIND_FAILURE:
        case ERROR_CONTACTDB_CHMOD_FAILURE:
        case ERROR_CONTACTDB_LISTEN_FAILURE:
        case STATUS_SUCCESS:
            return retval;

        default:
            return  ERROR_CONTACTDB_BIND_FAILURE;
    }
}
