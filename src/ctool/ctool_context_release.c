#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ctool_internal.h"

/* forward decls. */
static void cleanup_string(int* retval, char* string);

/**
 * \brief Release a ctool context.
 *
 * \param ctx           The context to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_context_release(ctool_context* ctx)
{
    int retval = STATUS_SUCCESS;

    /* release sock if set. */
    if (ctx->sock >= 0)
    {
        close(ctx->sock);
    }

    /* release strings. */
    cleanup_string(&retval, ctx->socket_path);
    cleanup_string(&retval, ctx->contact_form_name);
    cleanup_string(&retval, ctx->contact_form_email);
    cleanup_string(&retval, ctx->contact_form_subject);
    cleanup_string(&retval, ctx->contact_form_comment);

    /* clear and free context. */
    memset(ctx, 0, sizeof(*ctx));
    free(ctx);

    return retval;
}

/**
 * \brief Clean up a string, setting retval on failure.
 *
 * \param retval            Pointer to the return value, set on failure.
 * \param string            The string to clean up.
 */
static void cleanup_string(int* retval, char* string)
{
    int release_retval;

    if (NULL != string)
    {
        release_retval = string_release(string);
        if (STATUS_SUCCESS != release_retval)
        {
            *retval = release_retval;
        }
    }
}
