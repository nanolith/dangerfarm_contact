#include <errno.h>
#include <stdlib.h>

#include "../model_assert.h"
#include "unistd_internal.h"

int nondet_errno();

int close(int fd)
{
    int error = nondet_errno();

    MODEL_ASSERT(prop_is_valid_unix_desc(fd, DESC_TYPE_ANY, 0));

    free(unistd_desc_array[fd]);
    unistd_desc_array[fd] = NULL;

    switch (error)
    {
        case 0:
            errno = 0;
            return 0;

        case EBADF:
        case EINTR:
        case ENOSPC:
        #ifdef __FreeBSD__
        case ECONNRESET:
        #endif /* __FreeBSD__ */
        #ifdef __Linux__
        case EIO:
        case EDQUOT:
        #endif /* __Linux__ */
            errno = error;
            return -1;
    }
}
