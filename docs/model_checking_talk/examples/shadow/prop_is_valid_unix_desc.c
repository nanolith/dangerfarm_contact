#include <stddef.h>

#include "unistd_internal.h"

bool prop_is_valid_unix_desc(int d, int type, int flags)
{
    if (d < 0 || d >= SHADOW_DESC_COUNT)
        return false;

    desc* p = unistd_desc_array[d];

    if (NULL == p)
        return false;

    if (type != DESC_TYPE_ANY)
    {
        if (type != p->type)
            return false;
    }

    if (flags != 0)
    {
        if (flags & p->flags != flags)
            return false;
    }

    return true;
}
