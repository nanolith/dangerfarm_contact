#include "unix_shadow.h"

void unix_shadow_init()
{
    for (int i = 0; i < SHADOW_FD_COUNT; ++i)
    {
        __fd_shadow_list[i].desc = NULL;
    }
}
