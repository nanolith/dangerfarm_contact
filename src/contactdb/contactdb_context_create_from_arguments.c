#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"
#include "contactdb_context_create_from_arguments_internal.h"

/* forward decls. */
static void set_defaults(contactdb_context* ctx);
static int bind_local_socket(contactdb_context* ctx);

/**
 * \brief Given an argument count and vector, create a contactdb context.
 *
 * \param ctx           Pointer to the context pointer to be populated with the
 *                      context on success.
 * \param argc          The argument count.
 * \param argv          The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_context_create_from_arguments(
    contactdb_context** ctx, int argc, char* argv[])
{
    int retval, release_retval;
    contactdb_context* tmp = NULL;

    /* allocate memory for context. */
    tmp = (contactdb_context*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* set the defaults. */
    set_defaults(tmp);

    /* read command-line arguments. */
    retval = contactdb_context_create_from_arguments_read_args(tmp, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* if this is a listen socket, bind it. */
    if (tmp->listen_socket && NULL != tmp->socket_path)
    {
        retval = bind_local_socket(tmp);
        if (STATUS_SUCCESS != retval)
        {
            goto cleanup_tmp;
        }
    }

    /* connect to the database. */
    retval = contactdb_connection_create(&tmp->conn, tmp->db_path);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error connecting to the database.\n");
        goto cleanup_tmp;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    *ctx = tmp;
    goto done;

cleanup_tmp:
    release_retval = contactdb_context_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Set the defaults for this context.
 *
 * \brief ctx           The context to set up.
 */
static void set_defaults(contactdb_context* ctx)
{
    memset(ctx, 0, sizeof(*ctx));

    ctx->sock = -1;
    ctx->listen_socket = true;
}

/**
 * \brief Bind the local domain socket for this context.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int bind_local_socket(contactdb_context* ctx)
{
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
    unlink(addr.sun_path);

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
    memcpy(&addr, 0, sizeof(addr));

    return retval;
}
