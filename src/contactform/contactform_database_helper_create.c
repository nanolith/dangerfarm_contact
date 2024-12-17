#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
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
        close(socks[0]);
        *s = socks[1];
        retval = STATUS_SUCCESS;
        goto done;
    }

    /* child? */
    if (0 == *pid)
    {
        close(0); /* stdin. */
        close(1); /* stdout. */
        close(2); /* stderr. */
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
    return retval;
}
