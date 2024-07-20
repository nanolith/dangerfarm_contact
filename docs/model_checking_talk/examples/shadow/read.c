#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "../model_assert.h"
#include "unistd_internal.h"

int nondet_error();
size_t nondet_readbytes();
char nondet_char();

#define READ_MAX 8

ssize_t
read(int fd, void* buf, size_t nbytes)
{
    int error = nondet_error();
    char* cbuf = (char*)buf;

    /* verify that this is a valid descriptor for reading. */
    MODEL_ASSERT(prop_is_valid_unix_desc(fd, DESC_TYPE_ANY, O_RDONLY));

    /* does the read succeed? */
    if (0 == error)
    {
        /* compute the read size. */
        size_t readbytes = nondet_readbytes();
        if (readbytes > nbytes)
        {
            readbytes = nbytes;
        }

        /* set a byte at the end of the read range to verify memory access. */
        if (readbytes > 0)
        {
            cbuf[readbytes - 1] = nondet_char();
        }

        /* throw in some randomized bytes. */
        size_t read_max = readbytes > READ_MAX ? READ_MAX : readbytes;
        for (size_t i = 0; i < read_max; ++i)
        {
            cbuf[i] = nondet_char();
        }

        return (ssize_t)readbytes;
    }
    else
    {
        switch (error)
        {
            case EBADF:
            case ECONNRESET:
            case EFAULT:
            case EIO:
            case EBUSY:
            case EINTR:
            case EINVAL:
            case EAGAIN:
            case EISDIR:
            case EOPNOTSUPP:
            case EOVERFLOW:
            #ifdef __FreeBSD__
            case EINTEGRITY:
            #endif /* __FreeBSD__ */
            #ifdef __Linux__
            case EWOULDBLOCK:
            #endif /* __Linux__ */
                errno = error;
                return -1;

            default:
                errno = EBADF;
                return -1;
        }
    }
}
