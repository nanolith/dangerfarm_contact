#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stdbool.h>
#include <stddef.h>

bool prop_string_valid(const char* str)
{
    MODEL_ASSERT(NULL != str);

    return true;
}
