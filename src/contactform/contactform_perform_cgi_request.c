#include "contactform_internal.h"

/* forward decls. */
static int contactform_perform_cgi_options_request(contactform_context* ctx);
static int contactform_perform_cgi_post_request(contactform_context* ctx);
static int contactform_perform_cgi_bad_request(contactform_context* ctx);

/**
 * \brief Perform a CGI request action.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_perform_cgi_request(contactform_context* ctx)
{
    switch (ctx->request_type)
    {
        case CONTACTFORM_REQUEST_TYPE_OPTIONS:
            return contactform_perform_cgi_options_request(ctx);

        case CONTACTFORM_REQUEST_TYPE_POST:
            return contactform_perform_cgi_post_request(ctx);

        default:
            return contactform_perform_cgi_bad_request(ctx);
    }
}

/**
 * \brief Perform a CGI OPTIONS request action.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int contactform_perform_cgi_options_request(contactform_context* ctx)
{
    (void)ctx;

    return -1;
}

/**
 * \brief Perform a CGI POST request action.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int contactform_perform_cgi_post_request(contactform_context* ctx)
{
    (void)ctx;

    return -1;
}

/**
 * \brief Perform a CGI invalid request action.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int contactform_perform_cgi_bad_request(contactform_context* ctx)
{
    (void)ctx;

    return -1;
}
