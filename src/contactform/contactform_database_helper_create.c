#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <dangerfarm_contact/util/unix.h>
#include <unistd.h>

#include "contactform_internal.h"

/**
 * \brief Create a database helper connection.
 *
 * \param s             Pointer to the descriptor to be set to the socket to
 *                      set to the socket connection to the helper.
 * \param pid           Pointer to set to the process id of this helper.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_database_helper_create(int* s, pid_t* pid)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactform_database_helper_create, s, pid);

    int retval;
    int socks[2];

    /* create a socketpair. */
    retval = socketpair(AF_UNIX, SOCK_STREAM, 0, socks);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_CONTACTFORM_SOCKETPAIR;
        goto done;
    }

    /* fork the process. */
    *pid = fork();

    /* parent? */
    if (0 != *pid)
    {
        /* close the child socket endpoint. */
        close(socks[0]);

        /* return the parent socket endpoint. */
        *s = socks[1];

        /* success. */
        retval = STATUS_SUCCESS;
        goto done;
    }

    /* child? */
    if (0 == *pid)
    {
        /* close standard file descriptors. */
        close_fd(STDIN_FILENO);
        close_fd(STDOUT_FILENO);
        close_fd(STDERR_FILENO);

        /* close the parent socket endpoint. */
        close(socks[1]);

        /* we never return from here. */
        contactform_database_helper_entry(socks[0]);
    }

    /* If we make it here, fork failed, so report the error. */
    retval = ERROR_CONTACTFORM_FORK;
    goto cleanup_socks;

cleanup_socks:
    close(socks[0]);
    close(socks[1]);

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactform_database_helper_create, retval, s, pid);

    return retval;
}
