#include <errno.h>
#include <unistd.h>

int nondet_retval();

pid_t fork(void)
{
    int retval = nondet_retval();
    switch (retval)
    {
        case ENOMEM:
        case EAGAIN:
            errno = retval;
            return -1;

        case 0:
            break;

        default:
            errno = ENOMEM;
            return -1;
    }

    retval = nondet_retval();
    if (retval <= 0)
    {
        return 0;
    }
    else
    {
        return retval;
    }
}
