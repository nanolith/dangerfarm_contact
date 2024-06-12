#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

/* forward decls. */
static void set_defaults(contactdb_context* ctx);
static int read_args(contactdb_context* ctx, int argc, char* argv[]);
static int set_string(char** str, const char* opt, const char* value);
static int bind_local_socket(contactdb_context* ctx);

/**
 * \brief Given an argument count and vector, create a contactdb context.
 *
 * \brief ctx           Pointer to the context pointer to be populated with the
 *                      context on success.
 * \brief argc          The argument count.
 * \brief argv          The argument vector.
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
    retval = read_args(tmp, argc, argv);
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
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static void set_defaults(contactdb_context* ctx)
{
    memset(ctx, 0, sizeof(*ctx));

    ctx->sock = -1;
    ctx->listen_socket = true;
}

/**
 * \brief Read arguments, populating the context.
 *
 * \brief ctx           The context to populate with arguments.
 * \brief argc          The argument count.
 * \brief argv          The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int read_args(contactdb_context* ctx, int argc, char* argv[])
{
    int retval;
    int ch;

    while ((ch = getopt(argc, argv, "d:L:")) != -1)
    {
        switch (ch)
        {
            case 'd':
                retval = set_string(&ctx->db_path, "-d", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                break;

            case 'L':
                retval = set_string(&ctx->socket_path, "-L", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                ctx->listen_socket = true;
                break;
        }
    }

    /* verify that the database path was set. */
    if (NULL == ctx->db_path)
    {
        fprintf(stderr, "error: -d option is required.\n");
        retval = ERROR_CONTACTDB_MISSING_PARAMETER;
        goto done;
    }

    /* verify that the socket path was set. */
    if (NULL == ctx->socket_path)
    {
        fprintf(stderr, "error: -L option is required.\n");
        retval = ERROR_CONTACTDB_MISSING_PARAMETER;
        goto done;
    }

done:
    return retval;
}

/**
 * \brief Set the given string argument, returning an error if the string
 * argument was already set.
 *
 * \param str           The string argument to set.
 * \param opt           The option being set (for error logging).
 * \param value         The value to which this argument is set.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int set_string(char** str, const char* opt, const char* value)
{
    /* check for dupe. */
    if (NULL != *str)
    {
        fprintf(stderr, "%s parameter used twice!\n", opt);
        return ERROR_CONTACTDB_BAD_PARAMETER;
    }

    /* set the socket path. */
    *str = strdup(value);
    if (NULL == *str)
    {
        fprintf(stderr, "out of memory.\n");
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* success. */
    return STATUS_SUCCESS;
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
