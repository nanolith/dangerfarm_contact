#include "../../src/contactform/contactform_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    int s;
    int status;
    pid_t pid;

    /* create a database helper instance. */
    retval = contactform_database_helper_create(&s, &pid);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    close(s);
    waitpid(pid, &status, 0);

done:
    return retval;
}
