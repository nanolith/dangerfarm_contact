#include <dangerfarm_contact/cbmc/model_assert.h>
#include <unistd.h>

#include "unix_shadow.h"

int kill(pid_t pid, int sig)
{
    MODEL_ASSERT(prop_is_valid_unix_pid(pid));

    /* for the sake of model checking, assume kill works on known pids. */
    return 0;
}
