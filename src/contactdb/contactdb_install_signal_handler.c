#include <dangerfarm_contact/status_codes.h>
#include <signal.h>
#include <string.h>

#include "contactdb_internal.h"

/* forward decls. */
static void sighandler(int sig);
static contactdb_context* global_context = NULL;

/**
 * \brief Install a signal handler.
 *
 * \param ctx           The context to use for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_install_signal_handler(contactdb_context* ctx)
{
    int retval;
    struct sigaction sa;

    /* initialize the signal action. */
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &sighandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    /* register SIGHUP. */
    if (sigaction(SIGHUP, &sa, NULL) < 0)
    {
        retval = ERROR_CONTACTDB_SIGACTION_FAILURE;
        goto done;
    }

    /* register SIGTERM. */
    if (sigaction(SIGTERM, &sa, NULL) < 0)
    {
        retval = ERROR_CONTACTDB_SIGACTION_FAILURE;
        goto done;
    }

    /* register SIGINT. */
    if (sigaction(SIGINT, &sa, NULL) < 0)
    {
        retval = ERROR_CONTACTDB_SIGACTION_FAILURE;
        goto done;
    }

    /* save the context to the global context for the signal handler. */
    global_context = ctx;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}

/**
 * \brief Handle signals.
 *
 * \param sig           The signal to handle.
 */
static void sighandler(int sig)
{
    switch (sig)
    {
        /* ignore hang-up signal for now. */
        case SIGHUP:
            break;

        /* for all other signals, instruct the process to terminate. */
        default:
            global_context->should_terminate = true;
            break;
    }
}
