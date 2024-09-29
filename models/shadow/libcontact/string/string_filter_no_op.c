#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <string.h>

int DANGERFARM_CONTACT_SYM(string_filter)(char* str)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(string_filter), str);

    int retval;

    /* string_filter always succeeds. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(string_filter), retval, str);

    return retval;
}
