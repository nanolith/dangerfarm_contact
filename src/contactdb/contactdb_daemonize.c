#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/unix.h>
#include <unistd.h>

#include "contactdb_internal.h"

/**
 * \brief Daemonize the contactdb service.
 *
 * \param ctx           The context to use for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_daemonize(contactdb_context* ctx)
{
    int retval;

    /* install a signal handler. */
    retval = contactdb_install_signal_handler(ctx);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* fork to disassociate from the controlling terminal. */
    retval = fork();
    if (retval < 0)
    {
        retval = ERROR_CONTACTDB_FORK;
        goto done;
    }

    /* if this is the parent process, then we want to terminate. */
    if (0 != retval)
    {
        retval = ERROR_CONTACTDB_FORK_PARENT;
        goto done;
    }

    /* create a new session id. */
    pid_t session_id = setsid();
    if (session_id < 0)
    {
        retval = ERROR_CONTACTDB_SETSID;
        goto done;
    }

    /* fork again to create a non-group-leader process. */
    retval = fork();
    if (retval < 0)
    {
        retval = ERROR_CONTACTDB_FORK;
        goto done;
    }

    /* if this is the parent process, terminate. */
    if (0 != retval)
    {
        retval = ERROR_CONTACTDB_FORK_PARENT;
        goto done;
    }

    /* close standard file descriptors. */
    close_fd(STDIN_FILENO);
    close_fd(STDOUT_FILENO);
    close_fd(STDERR_FILENO);

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
