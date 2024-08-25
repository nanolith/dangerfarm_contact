#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stdlib.h>
#include <string.h>

int nondet_retval();

int strcmp(const char *s1, const char *s2)
{
    MODEL_ASSERT(NULL != s1);
    MODEL_ASSERT(NULL != s2);

    int retval = nondet_retval();

    switch (nondet_retval())
    {
        case 0:
        case -1:
        case 1:
            return retval;

        default:
            return -1;
    }
}
