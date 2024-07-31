#include <dangerfarm_contact/status_codes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <kcgi.h>

#include "contactform_internal.h"

#define KEY_MAX 0

static struct kvalid keys[] = { {NULL, NULL} };

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

    return -1;
}
