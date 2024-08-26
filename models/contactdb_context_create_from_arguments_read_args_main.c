#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>
#include <stdlib.h>

#include "../src/contactdb/contactdb_context_create_from_arguments_internal.h"

int simple_create_context(contactdb_context** ctx)
{
    *ctx = malloc(sizeof(contactdb_context));
    if (NULL == *ctx)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    memset(*ctx, 0, sizeof(contactdb_context));
    (*ctx)->sock = -1;

    return STATUS_SUCCESS;
}

int main(int argc, char* argv[])
{
    int retval;
    contactdb_context* ctx;

    /* create a simple context. */
    retval = simple_create_context(&ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* attempt to read arguments to populate the context. */
    retval =
        contactdb_context_create_from_arguments_read_args(ctx, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_ctx;
    }

    /* on success... */
    MODEL_ASSERT(STATUS_SUCCESS == retval);
    /* the db path is set. */
    MODEL_ASSERT(NULL != ctx->db_path);
    /* the socket path is set. */
    MODEL_ASSERT(NULL != ctx->socket_path);
    /* the capabilities are set. */
    MODEL_ASSERT(0 != ctx->root_capabilities);

cleanup_ctx:
    retval = contactdb_context_release(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
    }

done:
    return retval;
}
