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

    /* verify read access. */
    MODEL_CHECK_OBJECT_READ(cbuf, nbytes);

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
