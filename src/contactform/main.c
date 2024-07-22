#include <dangerfarm_contact/status_codes.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

#include "contactform_internal.h"

int main(int argc, char* argv[])
{
    int retval, release_retval, dbproc_retval;
    int dbsock;
    pid_t dbpid;
    (void)argc;
    (void)argv;

    /* create the database helper instance. */
    retval = contactform_database_helper_create(&dbsock, &dbpid);
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
        goto cleanup_dbpid;
    }

    /* drop privileges prior to performing CGI actions. */
    retval = contactform_drop_privileges(DROP_PRIV_STEP_COMPLETE);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_dbpid;
    }

    /* success. */
    retval = 0;
    goto cleanup_dbpid;

cleanup_dbpid:
    /* send a signal to kill the child process. */
    release_retval = kill(dbpid, SIGTERM);
    if (release_retval < 0)
    {
        retval = 1;
    }

    /* wait on the child pid. */
    release_retval = waitpid(dbpid, &dbproc_retval, 0);
    if (release_retval < 0)
    {
        retval = 1;
    }

    /* close the database socket. */
    close(dbsock);

done:
    return retval;
}
