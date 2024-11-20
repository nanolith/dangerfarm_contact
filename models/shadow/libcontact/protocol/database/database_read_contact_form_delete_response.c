#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();
uint32_t nondet_status();

int DANGERFARM_CONTACT_SYM(database_read_contact_form_delete_response)(
    uint32_t* status, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_delete_response),
        status, s);

    /* does this fail? */
    int retval = nondet_retval();
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* get the status. */
    *status = nondet_status();

    /* is this a bad status? */
    if (ERROR_INVALID_STATUS == *status)
    {
        retval = ERROR_INVALID_STATUS;
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *status = ERROR_INVALID_STATUS;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_delete_response),
        retval, status);

    return retval;
}
