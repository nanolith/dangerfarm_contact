#include <dangerfarm_contact/cbmc/model_assert.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int retval;

    /* fork this process. */
    pid = fork();
    /* child */
    if (0 == pid)
    {
        retval = 0;
        goto done;
    }
    else if (pid > 0)
    {
        /* wait on the pid. */
        int status = 0;
        pid_t rpid = waitpid(pid, &status, 0);
        if (rpid < 0)
        {
            retval = 1;
            goto done;
        }

        MODEL_ASSERT(rpid == pid);

        retval = 0;
        goto done;
    }
    /* error case. */
    else
    {
        retval = 1;
        goto done;
    }

done:
    return retval;
}
