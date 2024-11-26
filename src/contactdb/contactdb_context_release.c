#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

DANGERFARM_CONTACT_IMPORT_util_string;

/**
 * \brief Release a contactdb context.
 *
 * \param ctx           The context to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_context_release(contactdb_context* ctx)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_context_release, ctx);

    int retval = STATUS_SUCCESS;
    int release_retval = STATUS_SUCCESS;

    /* disable the signal handler. */
    release_retval = contactdb_disable_signal_handler(ctx);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

    /* if the connection is set, release it. */
    if (NULL != ctx->conn)
    {
        release_retval = contactdb_connection_release(ctx->conn);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* if the socket is set, close it. */
    if (ctx->sock >= 0)
    {
        close(ctx->sock);
    }

    /* if the socket_path is set, release it. */
    if (NULL != ctx->socket_path)
    {
        release_retval = string_release(ctx->socket_path);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* if the db_path is set, release it. */
    if (NULL != ctx->db_path)
    {
        release_retval = string_release(ctx->db_path);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* clean up the context. */
    memset(ctx, 0, sizeof(*ctx));
    free(ctx);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(contactdb_context_release, retval);

    return retval;
}
