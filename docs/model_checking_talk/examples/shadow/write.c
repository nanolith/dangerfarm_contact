#include <errno.h>
#include <unistd.h>

#include "../model_assert.h"
#include "unistd_internal.h"

int nondet_error();
size_t nondet_writebytes();

ssize_t write(int fd, const void* buf, size_t nbytes)
{
    int error = nondet_error();
    const char* cbuf = (const char*)buf;

    /* verify that this is a valid descriptor for writing. */
    MODEL_ASSERT(prop_is_valid_unix_desc(fd, DESC_TYPE_ANY, FLAG_WRITE));

    /* does the write succeed? */
    if (0 == error)
    {
        /* compute the write size. */
        size_t writebytes = nondet_writebytes();
        if (writebytes > nbytes)
        {
            writebytes = nbytes;
        }

        /* verify read access. */
        MODEL_ASSERT(cbuf[0] == cbuf[0]);
        if (writebytes > 0)
        {
            MODEL_ASSERT(cbuf[writebytes - 1] == cbuf[writebytes - 1]);
        }

        return (ssize_t)writebytes;
    }
    else
    {
        switch (error)
        {
            case EBADF:
            case EPIPE:
            case EFBIG:
            case EFAULT:
            case EINVAL:
            case ENOSPC:
            case EDQUOT:
            case EIO:
            case EINTR:
            case EAGAIN:
            #ifdef __FreeBSD__
            case EINTEGRITY:
            case EROFS:
            #endif /* __FreeBSD__ */
            #ifdef __Linux__
            case EWOULDBLOCK:
            case EDESTADDRREQ:
            case EPERM:
            #endif /* __Linux__ */
                errno = error;
                return -1;

            default:
                error = EBADF;
                return -1;
        }
    }
}
