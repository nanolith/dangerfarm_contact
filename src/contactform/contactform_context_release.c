#include <dangerfarm_contact/status_codes.h>
#include <signal.h>
#include <sys/wait.h>

#include "contactform_internal.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

/**
 * \brief Release a \ref contactform_context instance.
 *
 * \param ctx           The context to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_context_release(contactform_context* ctx)
{
    int retval = STATUS_SUCCESS, release_retval;
    int dummy_retval;

    /* close the socket if open. */
    if (ctx->dbsock >= 0)
    {
        release_retval = close(ctx->dbsock);
        if (release_retval < 0)
        {
            retval = ERROR_CONTACTFORM_DBSOCK_CLOSE;
        }
    }

    /* kill the child process if spawned. */
    if (ctx->dbpid > 1)
    {
        /* kill the child process. */
        release_retval = kill(ctx->dbpid, SIGTERM);
        if (release_retval < 0)
        {
            retval = ERROR_CONTACTFORM_DBPID_KILL;
        }
        else
        {
            /* wait on the child process. */
            release_retval = waitpid(ctx->dbpid, &dummy_retval, 0);
            if (release_retval < 0)
            {
                retval = ERROR_CONTACTFORM_DBPID_WAIT;
            }
        }
    }

    /* release the contact form if created. */
    if (NULL != ctx->form)
    {
        release_retval = contact_form_release(ctx->form);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release req if initialized. */
    if (ctx->kreq_initialized)
    {
        khttp_free(&ctx->req);
    } 

    return retval;
}
