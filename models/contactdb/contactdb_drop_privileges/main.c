#include <dangerfarm_contact/status_codes.h>

#include "../src/contactdb/contactdb_internal.h"

int main(int argc, char* argv[])
{
    int retval, release_retval;
    contactdb_context* ctx;

    /* create the context. */
    retval = contactdb_context_create_from_arguments(&ctx, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* drop privileges. */
    retval = contactdb_drop_privileges(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_ctx;
    }

    /* success. */
    retval = 0;
    goto cleanup_ctx;

cleanup_ctx:
    release_retval = contactdb_context_release(ctx);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = 1;
    }

done:
    return retval;
}