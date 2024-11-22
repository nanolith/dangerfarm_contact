#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();
uint32_t nondet_status();

int DANGERFARM_CONTACT_SYM(database_read_database_truncate_response)(
    uint32_t* status, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_database_truncate_response),
        status, s);

    /* does this operation fail? */
    int retval = nondet_retval();
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* read the status. */
    *status = nondet_status();
    if (ERROR_INVALID_STATUS == *status)
    {
        retval = ERROR_INVALID_STATUS;
        goto fail;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *status = ERROR_INVALID_STATUS;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_database_truncate_response),
        retval, status);

    return retval;
}
