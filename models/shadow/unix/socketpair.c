#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>

int nondet_int();

int socketpair(int domain, int type, int protocol, int *sv)
{
    /* these are the only options we support. */
    MODEL_ASSERT(AF_UNIX == domain);
    MODEL_ASSERT(SOCK_STREAM == type);
    MODEL_ASSERT(0 == protocol);

    /* make sure the buffer is large enough. */
    MODEL_ASSERT(NULL != sv);
    MODEL_CHECK_OBJECT_RW(sv, 2 * sizeof(int));

    int lhs = socket(domain, type, protocol);
    int rhs = socket(domain, type, protocol);

    if (lhs < 0 || rhs < 0)
    {
        if (lhs >= 0)
            close(lhs);

        if (rhs >= 0)
            close(rhs);

        int err = nondet_int();

        switch (err)
        {
            case EAFNOSUPPORT:
            case EOPNOTSUPP:
            case EPROTONOSUPPORT:
            #if defined(__FreeBSD__) || defined(__OpenBSD__)
            case EMFILE:
            case EFAULT:
            #endif
            #if defined(__Linux__)
            case ENFILE:
            case EACCES:
            case ENOMEM:
            #endif
            #if defined(__Linux__) || defined(__OpenBSD__)
            case EPROTOTYPE:
            case ENOBUFS:
            #endif
                errno = err;
                return -1;

            default:
                errno = EOPNOTSUPP;
                return -1;
        }
    }

    sv[0] = lhs;
    sv[1] = rhs;

    return 0;
}
