#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>

char nondet_char();

int DANGERFARM_CONTACT_SYM(string_create)(
    char** str, const void* data, size_t size)
{
    /* verify that all bytes of data are reachable. */
    MODEL_CHECK_OBJECT_READ(data, size);

    /* truncate string to speed up analysis. */
    if (size > 6) size = 6;

    char* tmp = (char*)malloc(size + 1);
    if (NULL == tmp)
    {
        *str = NULL;
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
