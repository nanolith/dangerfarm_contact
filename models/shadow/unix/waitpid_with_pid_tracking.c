#include <errno.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_status();

int choose_status()
{
    int retval = nondet_status();

    MODEL_ASSUME(WIFEXITED(retval));
    MODEL_ASSUME(WEXITSTATUS(retval) >= 0 && WEXITSTATUS(retval) <= 128);

    return retval;
};

pid_t waitpid(pid_t wpid, int *status, int options)
{
    /* we currently expect a normal blocking wait. */
    MODEL_ASSERT(0 == options);
    /* the pid should be in the reserved range. */
    MODEL_ASSERT(wpid >= 1 && wpid <= SHADOW_PID_COUNT);
    /* the pid should be one that has been reserved. */
    MODEL_ASSERT(NULL != __pid_shadow_list[wpid - 1].desc);

    /* reclaim the pid. */
    free(__pid_shadow_list[wpid - 1].desc);
    __pid_shadow_list[wpid - 1].desc = NULL;

    /* choose a return status from the process. */
    *status = choose_status();

    return wpid;
}
