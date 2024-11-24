#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "../../../src/contactdb/contactdb_context_create_from_arguments_internal.h"

int nondet_retval();

int contactdb_context_create_from_arguments_bind_local_socket(
    contactdb_context* ctx)
{
    ctx->sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (ctx->sock < 0)
    {
        return ERROR_CONTACTDB_BIND_FAILURE;
    }

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
            return ERROR_CONTACTDB_BIND_FAILURE;
    }
}
