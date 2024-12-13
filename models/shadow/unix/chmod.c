#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <sys/stat.h>

#include "unix_shadow.h"

int nondet_retval();

int chmod(const char *path, mode_t mode)
{
    MODEL_ASSERT(NULL != path);
    MODEL_ASSERT((S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) == mode);

    int retval = nondet_retval();

    switch (retval)
    {
        case 0:
            return 0;

        case EACCES:
        case EFAULT:
        case EFTYPE:
        #ifndef __OpenBSD__
        case EINTEGRITY:
        #endif
        case EIO:
        case ELOOP:
        case ENAMETOOLONG:
        case ENOENT:
        case ENOTDIR:
        case EPERM:
        case EROFS:
            errno = retval;
            return -1;

        default:
            errno = EACCES;
            return -1;
    }
}
