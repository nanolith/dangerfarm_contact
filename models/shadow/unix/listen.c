#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>

#include "unix_shadow.h"

int nondet_retval();

int listen(int s, int backlog)
{
    MODEL_ASSERT(prop_is_open_fd(s));
    MODEL_ASSERT(backlog > 0);

    int retval = nondet_retval();

    switch (retval)
    {
        case 0:
            return 0;

        case EBADF:
        case EDESTADDRREQ:
        case EINVAL:
        case ENOTSOCK:
        case EOPNOTSUPP:
            errno = retval;
            return -1;

        default:
            errno = EBADF;
            return -1;
    }
}
