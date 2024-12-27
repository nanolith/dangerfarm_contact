#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#ifdef __FreeBSD__
#include <sys/capsicum.h>
#endif /* __FreeBSD__ */

int nondet_retval();

int cap_enter(void)
{
    int retval = nondet_retval();

    switch (retval)
    {
        case STATUS_SUCCESS:
            return STATUS_SUCCESS;

        case EFAULT:
        case ENOSYS:
            errno = retval;
            return -1;

        default:
            errno = ENOSYS;
            return -1;
    }
}
