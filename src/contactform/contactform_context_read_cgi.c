#include <dangerfarm_contact/status_codes.h>

#include "contactform_internal.h"

static struct kvalid keys[] = {
    { kvalid_string, "name" },
    { kvalid_string, "email" },
    { kvalid_string, "subject" },
    { kvalid_string, "comment" },
};

enum page
{
    PAGE_CONTACTFORM,
    PAGE_MAX
};

static const char* pages[] = {
    "contactform"
};

/**
 * \brief Parse the CGI content, creating a contact form to send to the helper.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_context_read_cgi(contactform_context* ctx)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactform_context_read_cgi, ctx);

    int retval;

    /* parse http request. */
    retval =
        khttp_parsex(
            &ctx->req, ksuffixmap, kmimetypes, KMIME__MAX, keys, KEY_MAX, pages,
            PAGE_MAX, KMIME_TEXT_HTML, PAGE_CONTACTFORM,
            ctx, (void (*)(void*))&contactform_context_child_cleanup, 0, NULL);
    if (KCGI_OK != retval)
    {
        retval = ERROR_CONTACTFORM_KHTTP_PARSE;
        goto done;
    }

    /* the kcgi request context has been initialized. */
    ctx->kreq_initialized = true;

    /* decode the request type. */
    ctx->request_type =
        contactform_context_decode_request_type(ctx->req.method);

    /* if this is a post, decode a contact form. */
    if (CONTACTFORM_REQUEST_TYPE_POST == ctx->request_type)
    {
        retval = contactform_form_decode(ctx);
        if (STATUS_SUCCESS != retval)
        {
            goto done;
        }
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(contactform_context_read_cgi, retval);

    return retval;
}
