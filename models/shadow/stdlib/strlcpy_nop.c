#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stddef.h>

size_t nondet_size();

size_t strlcpy(char * restrict dst, const char * restrict src, size_t dstsize)
{
    MODEL_ASSERT(NULL != dst);
    MODEL_ASSERT(NULL != src);
    MODEL_ASSERT(dstsize > 0);
    MODEL_CHECK_OBJECT_RW(dst, dstsize);

    size_t retsize = nondet_size();
    if (retsize > dstsize)
    {
        retsize = dstsize;
    }

    /* randomize the output of dst. */
    __CPROVER_havoc_object(dst);
    /* ensure that dst is NUL terminated. */
    dst[dstsize - 1] = 0;

    return retsize;
}
