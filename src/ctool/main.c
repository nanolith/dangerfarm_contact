#include <dangerfarm_contact/status_codes.h>
#include <stdio.h>

#include "ctool_internal.h"

/**
 * \brief Main entry point for ctool.
 *
 * \param argc          The argument count.
 * \param argv          The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int main(int argc, char* argv[])
{
    ctool_context* ctx;
    int retval, release_retval;

    /* create the ctool context. */
    retval = ctool_context_create_from_arguments(&ctx, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    printf("Not yet implemented.\n");
    retval = 1;
    goto cleanup_ctx;

cleanup_ctx:
    release_retval = ctool_context_release(ctx);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = 2;
    }

done:
    return retval;
}
