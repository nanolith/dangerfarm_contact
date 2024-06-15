#include <dangerfarm_contact/status_codes.h>
#include <stdio.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

int main(int argc, char* argv[])
{
    contactdb_context* ctx;
    int retval, release_retval;

    /* create the contactdb context. */
    retval = contactdb_context_create_from_arguments(&ctx, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* loop while listening for connections. */
    while (!ctx->should_terminate)
    {
        retval = contactdb_accept_and_dispatch(ctx);
        if (STATUS_SUCCESS != retval)
        {
            goto cleanup_ctx;
        }
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_ctx;

cleanup_ctx:
    release_retval = contactdb_context_release(ctx);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = 2;
    }

done:
    return retval;
}
