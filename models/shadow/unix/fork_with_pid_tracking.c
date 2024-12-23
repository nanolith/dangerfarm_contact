#include <errno.h>
#include <unistd.h>

#include "unix_shadow.h"

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
        if (retval >= SHADOW_PID_COUNT)
        {
            retval = SHADOW_PID_COUNT;
        }

        __pid_shadow_list[retval - 1].desc = strdup("a");
        if (NULL == __pid_shadow_list[retval - 1].desc)
        {
            errno = ENOMEM;
            return -1;
        }
        else
        {
            return retval;
        }
    }
}
