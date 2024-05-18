#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <string.h>

int string_filter(char* str)
{
    /* verify that all bytes of data are reachable. */
    size_t length = strlen(str);
    MODEL_ASSERT(str[0] == str[0]);
    MODEL_ASSERT(str[length] == str[length] && str[length] == 0);

    /* string_filter always succeeds. */
    return STATUS_SUCCESS;
}
