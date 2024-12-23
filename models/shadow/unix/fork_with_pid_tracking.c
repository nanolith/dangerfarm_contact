#include <errno.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_retval();

pid_t fork(void)
{
    /* determine whether this call succeeds. */
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

    /* get the new pid. */
    retval = nondet_retval();
    if (retval <= 0)
    {
        return 0;
    }
    else
    {
        /* clamp the value to the PID count. */
        if (retval >= SHADOW_PID_COUNT)
        {
            retval = SHADOW_PID_COUNT;
        }

        /* if the pid is already taken, this is an error. */
        if (NULL != __pid_shadow_list[retval - 1].desc)
        {
            errno = ENOMEM;
            return -1;
        }

        /* reserve this pid so we can track that it is freed. */
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
