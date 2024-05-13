#include <dangerfarm_contact/cbmc/model_assert.h>
#include "unix_shadow.h"

bool prop_is_open_fd()
{
    MODEL_ASSERT(fd >= 0 && fd <= SHADOW_FD_COUNT);

    if (NULL == __fd_shadow_list[fd].desc)
    {
        return false;
    }

    return true;
}
