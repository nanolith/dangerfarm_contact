#include <dangerfarm_contact/status_codes.h>
#include <stdio.h>

#include "contactform_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    (void)argc;
    (void)argv;

    /* drop privileges prior to parsing CGI. */
    retval = contactform_drop_privileges(DROP_PRIV_STEP_KCGI_PARSE);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* drop privileges prior to performing CGI actions. */
    retval = contactform_drop_privileges(DROP_PRIV_STEP_COMPLETE);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* success. */
    retval = 0;
    goto done;

done:
    return retval;
}
