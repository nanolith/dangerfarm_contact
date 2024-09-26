#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>

char nondet_char();

int DANGERFARM_CONTACT_SYM(string_create)(
    char** str, const void* data, size_t size)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(string_create), str, data, size);

    int retval;

    /* verify that all bytes of data are reachable. */
    MODEL_CHECK_OBJECT_READ(data, size);

    /* truncate string to speed up analysis. */
    if (size > 6) size = 6;

    char* tmp = (char*)malloc(size + 1);
    if (NULL == tmp)
    {
        *str = NULL;
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    char contents_nondet[size];
    __CPROVER_array_replace((char*)tmp, contents_nondet);

    tmp[size] = 0;
    *str = tmp;
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(string_create), retval, str, size);

    return retval;
}
