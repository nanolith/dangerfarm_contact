#include <dangerfarm_contact/status_codes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "contactdb_context_create_from_arguments_internal.h"

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
int contactdb_context_create_from_arguments_read_args(
    contactdb_context* ctx, int argc, char* argv[])
{
    int retval;
    int ch;

    while ((ch = getopt(argc, argv, "r:d:L:")) != -1)
    {
        switch (ch)
        {
            /* database directory option. */
            case 'd':
                retval =
                    contactdb_context_create_from_arguments_set_string(
                        &ctx->db_path, "-d", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                break;

            /* listen socket path option. */
            case 'L':
                retval =
                    contactdb_context_create_from_arguments_set_string(
                        &ctx->socket_path, "-L", optarg);
                if (STATUS_SUCCESS != retval)
                {
                    goto done;
                }
                ctx->listen_socket = true;
                break;

            /* role option. */
            case 'r':
                /* set the web app role. */
                if (!strcmp("app", optarg))
                {
                    ctx->root_capabilities = DATABASE_ROLE_WEB_APPLICATION;
                }
                else if (!strcmp("admin", optarg))
                {
                    ctx->root_capabilities = DATABASE_ROLE_ADMIN_TOOL;
                }
                else
                {
                    fprintf(stderr, "error: unsupported role %s.\n", optarg);
                    retval = ERROR_CONTACTDB_INVALID_ROLE;
                    goto done;
                }
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

    /* verify that a role was set. */
    if (0 == ctx->root_capabilities)
    {
        fprintf(stderr, "error: -r option is required.\n");
        retval = ERROR_CONTACTDB_MISSING_PARAMETER;
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
