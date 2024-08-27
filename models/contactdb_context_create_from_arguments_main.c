#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>
#include <stdlib.h>

#include "../src/contactdb/contactdb_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    contactdb_context* ctx;

    /* create a context from arguments. */
    retval = contactdb_context_create_from_arguments(&ctx, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

cleanup_ctx:
    retval = contactdb_context_release(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
    }

done:
    return retval;
}
