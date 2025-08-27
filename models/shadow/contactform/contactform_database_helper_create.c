#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <dangerfarm_contact/util/unix.h>
#include <unistd.h>

#include "../../../src/contactform/contactform_internal.h"

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

    /* did fork fail? */
    if (*pid < 0)
    {
        retval = ERROR_CONTACTFORM_FORK;
        goto cleanup_socks;
    }

    /* parent? */
    if (0 != *pid)
    {
        /* close the child socket endpoint. */
        close(socks[0]);
        socks[0] = -1;

        /* return the parent socket endpoint. */
        *s = socks[1];

        /* success. */
        retval = STATUS_SUCCESS;
        goto done;
    }

    /* If we make it here, fork failed, so report the error. */
    retval = ERROR_CONTACTFORM_FORK;
    goto cleanup_socks;

cleanup_socks:
    if (socks[0] >= 0)
    {
        close(socks[0]);
    }
    if (socks[1] >= 0)
    {
        close(socks[1]);
    }

done:
    if (STATUS_SUCCESS != retval)
    {
        *s = -1;
        *pid = -1;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactform_database_helper_create, retval, s, pid);

    return retval;
}
