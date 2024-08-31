#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>

#include "../src/contactdb/contactdb_internal.h"

uint64_t nondet_capabilities();

uint64_t choose_capability()
{
    uint64_t retval = nondet_capabilities();

    switch (retval)
    {
        case DATABASE_CAPABILITY_CONTACT_FORM_APPEND:
        case DATABASE_CAPABILITY_CONTACT_FORM_GET:
        case DATABASE_CAPABILITY_CONTACT_FORM_DELETE:
        case DATABASE_CAPABILITY_CONTACT_FORM_COUNT_GET:
        case DATABASE_CAPABILITY_CONTACT_FORM_LIST_GET:
        case DATABASE_CAPABILITY_TRUNCATE:
            return retval;

        default:
            return DATABASE_CAPABILITY_CONTACT_FORM_GET;
    }
}

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

    /* test against any caps. */
    uint64_t cap = choose_capability();
    ctx->root_capabilities = nondet_capabilities();

    /* if the capability is set, then we can unset it. */
    if (contactdb_has_capability(ctx, cap))
    {
        ctx->root_capabilities ^= cap;
        MODEL_ASSERT(!contactdb_has_capability(ctx, cap));
    }
    else
    {
        ctx->root_capabilities ^= cap;
        MODEL_ASSERT(contactdb_has_capability(ctx, cap));
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
