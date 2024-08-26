#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "unix_shadow.h"

int nondet_retval();

int bind(int s, const struct sockaddr *addr, socklen_t addrlen)
{
    MODEL_ASSERT(prop_is_open_fd(s));
    MODEL_ASSERT(NULL != addr);
    MODEL_ASSERT(addrlen == sizeof(struct sockaddr_un));

    int retval = nondet_retval();

    switch (retval)
    {
        case 0:
            return 0;

        case EACCES:
        case EADDRINUSE:
        case EADDRNOTAVAIL:
        case EAFNOSUPPORT:
        case EAGAIN:
        case EBADF:
        case EFAULT:
        case EINTEGRITY:
        case EINVAL:
        case EIO:
        case EISDIR:
        case ELOOP:
        case ENAMETOOLONG:
        case ENOENT:
        case ENOTDIR:
        case ENOTSOCK:
        case EROFS:
            return retval;

        default:
            return EINVAL;
    }
}
