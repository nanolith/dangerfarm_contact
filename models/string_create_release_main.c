#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int retval;
    char* str = NULL;
    const char* INPUT = "foo bar b";
    const size_t INPUT_SIZE = strlen(INPUT);

    /* basic exercise of string creation. */
    retval = string_create(&str, INPUT, INPUT_SIZE);
    if (STATUS_SUCCESS != retval)
    {
        return 0;
    }

    /* the string is ASCIIZ as expected. */
    MODEL_ASSERT(0 == str[INPUT_SIZE]);

    /* basic exercise of string release. */
    retval = string_release(str);
    if (STATUS_SUCCESS != retval)
    {
        return 0;
    }

    return 0;
}
