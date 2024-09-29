#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <string.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(string_filter)(char* str)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(string_filter), str);

    int retval;

    retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
        case ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE:
        case ERROR_READ_MULTIBYTE_EOF:
        case ERROR_READ_MULTIBYTE_INVALID_CONTINUATION:
        case ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION:
        case ERROR_READ_MULTIBYTE_RAW_CONTINUATION:
        case ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER:
            goto done;

        default:
            retval = STATUS_SUCCESS;
            goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(string_filter), retval, str);

    return retval;
}
