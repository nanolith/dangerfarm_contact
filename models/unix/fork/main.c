#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int retval;

    /* fork this process. */
    pid = fork();
    if (0 == pid)
    {
        /* child */
        retval = 0;
        goto done;
    }
    else if (pid > 0)
    {
        /* parent. */
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
