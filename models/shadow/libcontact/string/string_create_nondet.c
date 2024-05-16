#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>

char nondet_char();

int string_create(char** str, const void* data, size_t size)
{
    /* verify that all bytes of data are reachable. */
    const char* bdata = (const char*)data;
    if (size >= 1)
    {
        MODEL_ASSERT(bdata[0] == bdata[0]);
        MODEL_ASSERT(bdata[size - 1] == bdata[size - 1]);
    }

    /* truncate string to work within unroll rules. */
    if (size > 8) size = 8;

    char* tmp = (char*)malloc(size + 1);
    if (NULL == tmp)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    for (size_t i = 0; i < size; ++i)
    {
        tmp[i] = nondet_char();
    }

    tmp[size] = 0;
    *str = tmp;

    return STATUS_SUCCESS;
}
