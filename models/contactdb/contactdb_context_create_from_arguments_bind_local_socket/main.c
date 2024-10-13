#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>
#include <stdlib.h>

#include "../src/contactdb/contactdb_internal.h"
#include "../src/contactdb/contactdb_context_create_from_arguments_internal.h"
#include "shadow/unix/unix_shadow.h"

int simple_create_context(contactdb_context** ctx)
{
    *ctx = malloc(sizeof(contactdb_context));
    if (NULL == *ctx)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    memset(*ctx, 0, sizeof(contactdb_context));
    (*ctx)->sock = -1;
    (*ctx)->socket_path = strdup("x");
    if (NULL == (*ctx)->socket_path)
    {
        free(*ctx);
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

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

    /* attempt to bind the local socket. */
    retval = contactdb_context_create_from_arguments_bind_local_socket(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_ctx;
    }

    /* on success... */
    MODEL_ASSERT(STATUS_SUCCESS == retval);
    /* the socket is valid. */
    MODEL_ASSERT(prop_is_open_fd(ctx->sock));

cleanup_ctx:
    retval = contactdb_context_release(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
    }

done:
    return retval;
}
