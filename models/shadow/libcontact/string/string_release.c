#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>

int string_release(char* str)
{
    free(str);
    return STATUS_SUCCESS;
}
