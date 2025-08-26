#include <dangerfarm_contact/cbmc/model_assert.h>
#include <unistd.h>

#include "unix_shadow.h"

bool prop_is_valid_unix_pid(pid_t pid)
{
    MODEL_ASSERT(pid >= 1 && pid <= SHADOW_PID_COUNT);
    MODEL_ASSERT(NULL != __pid_shadow_list[pid - 1].desc);

    return true;
}
