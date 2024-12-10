#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "../../../src/contactdb/contactdb_context_create_from_arguments_internal.h"

int nondet_retval();

int contactdb_context_create_from_arguments_bind_local_socket(
    contactdb_context* ctx)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_context_create_from_arguments_bind_local_socket, ctx);

    int retval;

    ctx->sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (ctx->sock < 0)
    {
        retval = ERROR_CONTACTDB_BIND_FAILURE;
        goto done;
    }

    retval = nondet_retval();

    switch (retval)
    {
        case ERROR_CONTACTDB_SOCKET_PATH_TOO_LONG:
        case ERROR_CONTACTDB_SOCKET_FAILURE:
        case ERROR_CONTACTDB_UNLINK_FAILURE:
        case ERROR_CONTACTDB_BIND_FAILURE:
        case ERROR_CONTACTDB_CHMOD_FAILURE:
        case ERROR_CONTACTDB_LISTEN_FAILURE:
            goto cleanup_sock;

        case STATUS_SUCCESS:
            goto done;

        default:
            retval = ERROR_CONTACTDB_BIND_FAILURE;
            goto cleanup_sock;
    }

cleanup_sock:
    close(ctx->sock);
    ctx->sock = -1;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_context_create_from_arguments_bind_local_socket, retval, ctx);

    return retval;
}
