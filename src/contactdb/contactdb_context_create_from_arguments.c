#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"
#include "contactdb_context_create_from_arguments_internal.h"

/* forward decls. */
static void set_defaults(contactdb_context* ctx);

/**
 * \brief Given an argument count and vector, create a contactdb context.
 *
 * \param ctx           Pointer to the context pointer to be populated with the
 *                      context on success.
 * \param argc          The argument count.
 * \param argv          The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_context_create_from_arguments(
    contactdb_context** ctx, int argc, char* argv[])
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_context_create_from_arguments, ctx, argc, argv);

    int retval, release_retval;
    contactdb_context* tmp = NULL;

    /* allocate memory for context. */
    tmp = (contactdb_context*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto fail;
    }

    /* set the defaults. */
    set_defaults(tmp);

    /* read command-line arguments. */
    retval = contactdb_context_create_from_arguments_read_args(tmp, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* if this is a listen socket, bind it. */
    if (tmp->listen_socket && NULL != tmp->socket_path)
    {
        retval = contactdb_context_create_from_arguments_bind_local_socket(tmp);
        if (STATUS_SUCCESS != retval)
        {
            goto cleanup_tmp;
        }
    }

    /* connect to the database. */
    retval = contactdb_connection_create(&tmp->conn, tmp->db_path);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error connecting to the database.\n");
        goto cleanup_tmp;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    *ctx = tmp;
    goto done;

cleanup_tmp:
    release_retval = contactdb_context_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

fail:
    *ctx = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_context_create_from_arguments, retval, ctx);

    return retval;
}

/**
 * \brief Set the defaults for this context.
 *
 * \brief ctx           The context to set up.
 */
static void set_defaults(contactdb_context* ctx)
{
    memset(ctx, 0, sizeof(*ctx));

    ctx->sock = -1;
    ctx->listen_socket = true;
}
