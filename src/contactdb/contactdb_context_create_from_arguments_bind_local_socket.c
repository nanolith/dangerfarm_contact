#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include "contactdb_context_create_from_arguments_internal.h"

/**
 * \brief Bind the local domain socket for this context.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_context_create_from_arguments_bind_local_socket(
    contactdb_context* ctx)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_context_create_from_arguments_bind_local_socket, ctx);

    int retval;
    struct sockaddr_un addr;

    /* verify that the length of the socket path does not exceed sun_path. */
    if (strlen(ctx->socket_path) + 1 > sizeof(addr.sun_path))
    {
        retval = ERROR_CONTACTDB_SOCKET_PATH_TOO_LONG;
        goto done;
    }

    /* set the bind address. */
    addr.sun_family = AF_UNIX;
    strlcpy(addr.sun_path, ctx->socket_path, sizeof(addr.sun_path));

    /* create a socket. */
    ctx->sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (ctx->sock < 0)
    {
        retval = ERROR_CONTACTDB_SOCKET_FAILURE;
        goto done;
    }

    /* unlink the file before binding. */
    retval = unlink(addr.sun_path);
    if (retval < 0 && errno != ENOENT)
    {
        retval = ERROR_CONTACTDB_UNLINK_FAILURE;
        goto cleanup_sock;
    }

    /* bind this socket. */
    retval = bind(ctx->sock, (struct sockaddr*)&addr, sizeof(addr));
    if (retval < 0)
    {
        retval = ERROR_CONTACTDB_BIND_FAILURE;
        goto cleanup_sock;
    }

    /* make this socket only user / group readable / writeable. */
    retval = chmod(ctx->socket_path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (retval < 0)
    {
        retval = ERROR_CONTACTDB_CHMOD_FAILURE;
        goto cleanup_sock;
    }

    /* listen on this socket. */
    retval = listen(ctx->sock, 5);
    if (retval < 0)
    {
        retval = ERROR_CONTACTDB_LISTEN_FAILURE;
        goto cleanup_sock;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_sock:
    close(ctx->sock);
    ctx->sock = -1;

done:
    memset(&addr, 0, sizeof(addr));

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_context_create_from_arguments_bind_local_socket, retval, ctx);

    return retval;
}
