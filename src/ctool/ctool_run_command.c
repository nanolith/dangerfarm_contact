#include <dangerfarm_contact/status_codes.h>
#include <stdio.h>

#include "ctool_internal.h"

/**
 * \brief Run a ctool command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_command(ctool_context* ctx)
{
    int retval;

    switch (ctx->command)
    {
        case CTOOL_COMMAND_GET_COUNT:
            retval = ctool_run_get_count_command(ctx);
            break;

        default:
            fprintf(stderr, "Command not yet implemented.\n");
            retval = ERROR_CTOOL_INVALID_COMMAND;
            break;
    }

    return retval;
}
