#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_status();
size_t nondet_readbytes();
char nondet_char();

ssize_t
read(int fd, void* buf, size_t nbytes)
{
    char* cbuf = (char*)buf;

    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(fd));

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        /* compute the size read. */
        size_t readbytes = nondet_readbytes();
        if (readbytes > nbytes)
        {
            readbytes = nbytes;
        }

        char contents_nondet[readbytes];
        __CPROVER_array_replace((char*)buf, contents_nondet);

        return (ssize_t)readbytes;
    }
    else
    {
        errno = EBADF;
        return -1;
    }
}
