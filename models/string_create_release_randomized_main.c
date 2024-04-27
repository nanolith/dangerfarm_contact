#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>

int nondet_char();
static void randomize_string(char* str, size_t size)
{
    for (size_t i = 0; i < size; ++i) str[i] = nondet_char();
}

int main(int argc, char* argv[])
{
    int retval;
    char* str = NULL;
    char INPUT[9];
    const size_t INPUT_SIZE = sizeof(INPUT);

    randomize_string(INPUT, INPUT_SIZE);

    /* basic exercise of string creation. */
    retval = string_create(&str, INPUT, INPUT_SIZE);
    if (STATUS_SUCCESS != retval)
    {
        return 0;
    }

    /* the string is ASCIIZ as expected. */
    MODEL_ASSERT(0 == str[INPUT_SIZE]);

    /* NULL characters are not copied. */
    for (size_t i = 0; i < INPUT_SIZE; ++i)
    {
        MODEL_ASSERT(0 != str[i]);
    }

    /* basic exercise of string release. */
    retval = string_release(str);
    if (STATUS_SUCCESS != retval)
    {
        return 0;
    }

    return 0;
}
