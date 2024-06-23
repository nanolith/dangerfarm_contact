#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ctool_internal.h"

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
    int retval = STATUS_SUCCESS, release_retval;

    /* release socket_path if set. */
    if (NULL != ctx->socket_path)
    {
        release_retval = string_release(ctx->socket_path);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release sock if set. */
    if (ctx->sock >= 0)
    {
        close(ctx->sock);
    }

    /* release contact_form_name if set. */
    if (NULL != ctx->contact_form_name)
    {
        release_retval = string_release(ctx->contact_form_name);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release contact_form_email if set. */
    if (NULL != ctx->contact_form_email)
    {
        release_retval = string_release(ctx->contact_form_email);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release contact_form_subject if set. */
    if (NULL != ctx->contact_form_subject)
    {
        release_retval = string_release(ctx->contact_form_subject);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release contact_form_comment if set. */
    if (NULL != ctx->contact_form_comment)
    {
        release_retval = string_release(ctx->contact_form_comment);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* clear and free context. */
    memset(ctx, 0, sizeof(*ctx));
    free(ctx);

    return retval;
}
