#include <dangerfarm_contact/status_codes.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

#include "contactform_internal.h"

int main(int argc, char* argv[])
{
    int retval, release_retval;
    contactform_context* ctx;
    (void)argc;
    (void)argv;

    /* create the contactform context. */
    retval = contactform_context_create(&ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* drop privileges prior to parsing CGI. */
    retval = contactform_drop_privileges(DROP_PRIV_STEP_KCGI_PARSE);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_ctx;
    }

    /* parse the CGI request. */
    retval = contactform_context_read_cgi(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_ctx;
    }

    /* drop privileges prior to performing CGI actions. */
    retval = contactform_drop_privileges(DROP_PRIV_STEP_COMPLETE);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_ctx;
    }

    /* perform the CGI request. */
    retval = contactform_perform_cgi_request(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_ctx;
    }

    /* success. */
    retval = 0;
    goto cleanup_ctx;

cleanup_ctx:
    release_retval = contactform_context_release(ctx);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = 1;
    }

done:
    return retval;
}
