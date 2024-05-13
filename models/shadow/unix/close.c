#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <unistd.h>

#include "unix_shadow.h"

int close(int fd)
{
    MODEL_ASSERT(fd >= 0 && fd <= SHADOW_FD_COUNT);

    if (NULL == __fd_shadow_list[fd].desc)
    {
        errno = EBADF;
        return -1;
    }

    free(__fd_shadow_list[fd].desc);
    __fd_shadow_list[fd].desc = NULL;
    return 0;
}
