#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>

DANGERFARM_CONTACT_IMPORT_util_string;

int main(int argc, char* argv[])
{
    int retval;
    char* str;
    const char* INPUT = "1234567890abcdefg";
    size_t INPUT_SIZE = 18;

    retval = string_create(&str, INPUT, INPUT_SIZE);
    if (STATUS_SUCCESS != retval)
    {
        /* the only failure case this implementation supports is an allocation
         * error. */
        MODEL_ASSERT(ERROR_GENERAL_OUT_OF_MEMORY == retval);
        return 1;
    }

    /* clean up. */
    MODEL_ASSERT(STATUS_SUCCESS == string_release(str));

    return 0;
}
