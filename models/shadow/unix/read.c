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

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        /* compute the size read. */
        size_t readbytes = nondet_readbytes();
        if (readbytes > nbytes)
        {
            readbytes = nbytes;
        }

        /* set a byte at the end of the read range to prove access. */
        if (readbytes > 0)
        {
            cbuf[readbytes - 1] = nondet_char();
        }

        /* throw in some randomized bytes. */
        for (size_t i = 0; i < readbytes; ++i)
        {
            cbuf[i] = nondet_char();
        }

        return (ssize_t)readbytes;
    }
    else
    {
        errno = EBADF;
        return -1;
    }
}
