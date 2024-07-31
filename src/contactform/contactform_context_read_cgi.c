#include <dangerfarm_contact/status_codes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <kcgi.h>

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

#define PAGE_MAX 0

static const char* pages[] = {
    "contactform"
};

static const size_t defaultpage = 0;

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
    (void)ctx;
    (void)keys;
    (void)pages;
    (void)defaultpage;

    return -1;
}
