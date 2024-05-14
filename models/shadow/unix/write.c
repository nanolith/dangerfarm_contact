#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_status();
size_t nondet_wrotebytes();

ssize_t write(int fd, const void* buf, size_t nbytes)
{
    const char* cbuf = (const char*)buf;

    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(fd));

    /* read a byte from the beginning and end of the buffer to check access. */
    if (nbytes > 0)
    {
        char byte0 = buf[0];
        MODEL_ASSERT(byte0 == buf[0]);
        char byte1 = buf[nbytes - 1];
        MODEL_ASSERT(byte1 == buf[nbytes - 1]);
    }

    /* does this write succeed? */
    if (0 == nondet_status())
    {
        /* compute the bytes written. */
        size_t wrotebytes = nondet_wrotebytes();
        if (wrotebytes > nbytes)
        {
            wrotebytes = nbytes;
        }

        return (ssize_t)wrotebytes;
    }
    else
    {
        errno = EBADF;
        return -1;
    }
}
