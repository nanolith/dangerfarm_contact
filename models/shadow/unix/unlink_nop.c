#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <unistd.h>

int nondet_retval();

int unlink(const char *path)
{
    MODEL_ASSERT(NULL != path);

    int retval = nondet_retval();
    switch (retval)
    {
        case 0:
            return 0;

        case ENOTDIR:
        case EISDIR:
        case ENAMETOOLONG:
        case ENOENT:
        case EACCES:
        case ELOOP:
        case EPERM:
        case EIO:
        #ifndef __OpenBSD__
        case EINTEGRITY:
        #endif
        case EROFS:
        case EFAULT:
        case ENOSPC:
            errno = retval;
            return -1;
    }
}
