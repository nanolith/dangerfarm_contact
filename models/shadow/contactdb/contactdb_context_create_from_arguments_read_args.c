#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "../../../src/contactdb/contactdb_context_create_from_arguments_internal.h"

int nondet_retval();

int contactdb_context_create_from_arguments_read_args(
    contactdb_context* ctx, int argc, char* argv[])
{
    /* should we exit early with an error? */
    int retval = nondet_retval();
    switch (retval)
    {
        case ERROR_GENERAL_OUT_OF_MEMORY:
        case ERROR_CONTACTDB_BAD_PARAMETER:
        case ERROR_CONTACTDB_INVALID_ROLE:
        case ERROR_CONTACTDB_MISSING_PARAMETER:
            return retval;
    }

    /* create a db path. */
    ctx->db_path = strdup("x");
    if (NULL == ctx->db_path)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* create a socket path. */
    ctx->socket_path = strdup("x");
    if (NULL == ctx->socket_path)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* set the root capabilities. */
    switch (nondet_retval())
    {
        case DATABASE_ROLE_ADMIN_TOOL:
            ctx->root_capabilities = DATABASE_ROLE_ADMIN_TOOL;
            break;

        case DATABASE_ROLE_WEB_APPLICATION:
        default:
            ctx->root_capabilities = DATABASE_ROLE_WEB_APPLICATION;
            break;
    }

    return STATUS_SUCCESS;
}
