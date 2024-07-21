#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#include "unistd_internal.h"

int nondet_errno();

static int decode_flags(int flags)
{
    if (O_RDWR == flags)
    {
        return FLAG_READ | FLAG_WRITE;
    }
    else if (O_RDONLY == flags)
    {
        return FLAG_READ;
    }
    else if (O_WRONLY == flags)
    {
        return FLAG_WRITE;
    }
    else
    {
        return FLAG_NONE;
    }
}

int open(const char *path, int flags, ...)
{
    int error = nondet_errno();

    /* might this open succeed? */
    if (0 == error)
    {
        /* allocate a descriptor, if possible. */
        for (int i = 0; i < SHADOW_DESC_COUNT; ++i)
        {
            if (NULL == unistd_desc_array[i])
            {
                unistd_desc_array[i] = (desc*)malloc(sizeof(desc));
                if (NULL == unistd_desc_array[i])
                {
                    errno = ENOMEM;
                    return -1;
                }

                unistd_desc_array[i]->type = DESC_TYPE_FILE;
                unistd_desc_array[i]->flags = decode_flags(flags);
                errno = 0;
                return i;
            }

            errno = EMFILE;
            return -1;
        }
    }
    else
    {
        switch (error)
        {
            case ENOTDIR:
            case ENAMETOOLONG:
            case ENOENT:
            case EACCES:
            case EPERM:
            case ELOOP:
            case EISDIR:
            case EROFS:
            case EMFILE:
            case EMLINK:
            case ENXIO:
            case EINTR:
            case EOPNOTSUPP:
            case EWOULDBLOCK:
            case ENOSPC:
            case EDQUOT:
            case EIO:
            case ETXTBSY:
            case EFAULT:
            case EEXIST:
            case EOPNOTSUPP:
            case EINVAL:
            case EBADF:
            case ENOTDIR:
            #ifdef __FreeBSD__
            case EINTEGRITY:
            case ECAPMODE:
            case ENOTCAPABLE:
            #endif /* __FreeBSD__ */
            #ifdef __Linux__
            case EBUSY:
            case EFBIG:
            case ENFILE:
            case ENODEV:
            case ENOMEM:
            case EOVERFLOW:
            #endif /* __Linux__ */
                errno = error;

            default:
                errno = ENOENT;
        }

        return -1;
    }
}
