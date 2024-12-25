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
    MODEL_CHECK_OBJECT_RW(addr, addrlen);

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
        #ifndef __OpenBSD__
        case EINTEGRITY:
        #endif
        case EINVAL:
        case EIO:
        case EISDIR:
        case ELOOP:
        case ENAMETOOLONG:
        case ENOENT:
        case ENOTDIR:
        case ENOTSOCK:
        case EROFS:
            errno = retval;
            return -1;

        default:
            errno = EINVAL;
            return -1;
    }
}
