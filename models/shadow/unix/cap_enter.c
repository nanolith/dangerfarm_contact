#ifdef __FreeBSD__

#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <sys/capsicum.h>

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
#endif /* __FreeBSD__ */
