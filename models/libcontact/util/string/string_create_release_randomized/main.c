#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>

DANGERFARM_CONTACT_IMPORT_util_string;

int nondet_char();
static void randomize_string(char* str, size_t size)
{
    char contents_nondet[size];
    __CPROVER_array_replace((char*)str, contents_nondet);
}

size_t nondet_size();

static size_t randomized_size(size_t size)
{
    size_t retsize = nondet_size();
    if (retsize > size)
    {
        retsize = size;
    }

    return size;
}

int main(int argc, char* argv[])
{
    int retval;
    char* str = NULL;
    char INPUT[9];
    const size_t INPUT_SIZE = randomized_size(sizeof(INPUT));

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
