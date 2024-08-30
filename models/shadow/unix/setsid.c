#include <errno.h>
#include <unistd.h>

int nondet_retval();

pid_t setsid(void)
{
    int retval = nondet_retval();
    if (retval <= 0)
    {
        errno = retval;
        return -1;
    }

    return retval;
}
