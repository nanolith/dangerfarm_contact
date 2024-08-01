#include <dangerfarm_contact/status_codes.h>

#include "contactform_internal.h"

enum key
{
    KEY_NAME,
    KEY_EMAIL,
    KEY_SUBJECT,
    KEY_COMMENT,
    KEY_MAX
};

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
    int retval;
    struct kreq req;

    /* parse http request. */
    retval =
        khttp_parsex(
            &req, ksuffixmap, kmimetypes, KMIME__MAX, keys, KEY_MAX, pages,
            PAGE_MAX, KMIME_TEXT_HTML, PAGE_CONTACTFORM,
            ctx, (void (*)(void*))&contactform_context_child_cleanup, 0, NULL);
    if (KCGI_OK != retval)
    {
        retval = ERROR_CONTACTFORM_KHTTP_PARSE;
        goto done;
    }

    retval = -1;
    goto cleanup_req;

cleanup_req:
    khttp_free(&req);

done:
    return retval;
}
