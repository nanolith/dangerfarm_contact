#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    const char* VAL = "abc 123";
    char* dupe = NULL;

    /* attempt to duplicate a string. */
    dupe = strdup(VAL);
    if (NULL == dupe)
    {
        return 1;
    }

    free(dupe);

    return 0;
}
