#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <string.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(string_filter)(char* str)
{
    /* verify that all bytes of data are reachable. */
    size_t length = strlen(str);
    MODEL_ASSERT(str[0] == str[0]);
    MODEL_ASSERT(str[length] == str[length] && str[length] == 0);

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
        case ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE:
        case ERROR_READ_MULTIBYTE_EOF:
        case ERROR_READ_MULTIBYTE_INVALID_CONTINUATION:
        case ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION:
        case ERROR_READ_MULTIBYTE_RAW_CONTINUATION:
        case ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER:
            return retval;

        default:
            return STATUS_SUCCESS;
    }
}
