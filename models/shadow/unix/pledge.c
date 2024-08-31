#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <unistd.h>

int nondet_retval();

int pledge(const char *promises, const char *execpromises)
{
    int retval = nondet_retval();

    switch (retval)
    {
        case STATUS_SUCCESS:
            return STATUS_SUCCESS;

        case EFAULT:
        case EINVAL:
        case EPERM:
            errno = retval;
            return -1;

        default:
            errno = EPERM;
            return -1;
    }
}
