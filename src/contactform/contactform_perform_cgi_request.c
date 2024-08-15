#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>

#include "contactform_internal.h"

DANGERFARM_CONTACT_IMPORT_protocol_database;

/* forward decls. */
static int contactform_perform_cgi_options_request(contactform_context* ctx);
static int contactform_perform_cgi_post_request(contactform_context* ctx);
static int contactform_perform_cgi_bad_request(contactform_context* ctx);
static int output_standard_headers(contactform_context* ctx, int status_code);

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
    int retval;

    /* add the allow header. */
    retval = khttp_head(&ctx->req, kresps[KRESP_ALLOW], "OPTIONS POST");
    if (KCGI_OK != retval)
    {
        return ERROR_CONTACTFORM_KHTTP_HEAD;
    }

    /* add the standard headers. */
    return output_standard_headers(ctx, KHTTP_204);
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
    int retval;
    uint32_t status;

    /* send the contact form request to the database server, through our child
     * process. */
    retval = database_write_contact_form_append_request(ctx->dbsock, ctx->form);
    if (STATUS_SUCCESS != retval)
    {
        goto error_500;
    }

    /* read the response. */
    retval = database_read_contact_form_append_response(&status, ctx->dbsock);
    if (STATUS_SUCCESS != retval)
    {
        goto error_500;
    }

    /* did we fail? */
    if (STATUS_SUCCESS != status)
    {
        return output_standard_headers(ctx, KHTTP_400);
    }

    /* output headers. */
    retval = output_standard_headers(ctx, KHTTP_200);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* output body. */
    retval = khttp_puts(&ctx->req, "Contact Request Sent!");
    if (KCGI_OK != retval)
    {
        return ERROR_CONTACTFORM_KHTTP_PUTS;
    }

    return STATUS_SUCCESS;

error_500:
    return output_standard_headers(ctx, KHTTP_500);
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
    int retval;

    /* add the allow header. */
    retval = khttp_head(&ctx->req, kresps[KRESP_ALLOW], "OPTIONS POST");
    if (KCGI_OK != retval)
    {
        return ERROR_CONTACTFORM_KHTTP_HEAD;
    }

    /* add the standard headers. */
    return output_standard_headers(ctx, KHTTP_405);
}

/**
 * \brief Output the standard headers and close the header section of the
 * response.
 *
 * \param ctx           The context for this operation.
 * \param status_code   The KCGI http header code for this response.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int output_standard_headers(contactform_context* ctx, int status_code)
{
    int retval;

    /* add the status header. */
    retval =
        khttp_head(&ctx->req, kresps[KRESP_STATUS], "%s", khttps[status_code]);
    if (KCGI_OK != retval)
    {
        return ERROR_CONTACTFORM_KHTTP_HEAD;
    }

    /* add the content type header. */
    retval =
        khttp_head(
            &ctx->req, kresps[KRESP_CONTENT_TYPE], "%s",
            kmimetypes[KMIME_TEXT_PLAIN]);
    if (KCGI_OK != retval)
    {
        return ERROR_CONTACTFORM_KHTTP_HEAD;
    }

    /* Close the headers and start the body. */
    retval = khttp_body(&ctx->req);
    if (KCGI_OK != retval)
    {
        return ERROR_CONTACTFORM_KHTTP_BODY;
    }

    return STATUS_SUCCESS;
}
