#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/function_decl.h>
#include <stdbool.h>
#include <stddef.h>

bool DANGERFARM_CONTACT_SYM(prop_string_valid)(const char* str)
{
    MODEL_ASSERT(NULL != str);

    return true;
}
