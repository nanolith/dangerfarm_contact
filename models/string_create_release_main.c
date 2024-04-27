#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>

int main(int argc, char* argv[])
{
    int retval;
    char* str = NULL;
    const char* INPUT = "foo bar b";
    const size_t INPUT_SIZE = strlen(INPUT);

    retval = string_create(&str, INPUT, INPUT_SIZE);
    if (STATUS_SUCCESS != retval)
    {
        return 0;
    }

    retval = string_release(str);
    if (STATUS_SUCCESS != retval)
    {
        return 0;
    }

    return 0;
}
