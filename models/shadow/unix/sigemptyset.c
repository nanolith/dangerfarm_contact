#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>

int nondet_retval();

int sigemptyset(sigset_t *set)
{
    MODEL_ASSERT(NULL != set);

    int retval = nondet_retval();
    switch (retval)
    {
        case 0:
            return 0;

        case EINVAL:
        default:
            errno = EINVAL;
            return -1;
    }
}
