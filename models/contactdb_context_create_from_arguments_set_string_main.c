#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>

#include "../src/contactdb/contactdb_context_create_from_arguments_internal.h"

bool nondet_coinflip();

char* dupeval(bool* shouldfree)
{
    if (nondet_coinflip())
    {
        *shouldfree = false;
        return "value already set";
    }
    else
    {
        *shouldfree = true;
        return NULL;
    }
}

int main(int argc, char* argv[])
{
    int retval;
    const char* VAL = "abc 123";
    bool should_free_dupe = false;
    char* dupe = dupeval(&should_free_dupe);

    /* attempt to set a string. */
    retval =
        contactdb_context_create_from_arguments_set_string(&dupe, "-b", VAL);
    if (STATUS_SUCCESS != retval)
    {
        return 1;
    }

    /* free the dupe value if not a constant. */
    if (should_free_dupe)
    {
        free(dupe);
    }

    return 0;
}
