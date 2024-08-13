#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stdlib.h>
#include <string.h>

/* Quick and dirty string duplication shadow. */
char* strdup(const char* str)
{
    MODEL_ASSERT(NULL != str);

    char* ret = malloc(2);
    if (NULL != ret)
    {
        memcpy(ret, "x", 2);
    }

    return ret;
}
