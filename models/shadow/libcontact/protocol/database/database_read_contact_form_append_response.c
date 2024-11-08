#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();
uint32_t nondet_status();

int DANGERFARM_CONTACT_SYM(database_read_contact_form_append_response)(
    uint32_t* status, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_append_response),
        status, s);

    int retval = nondet_retval();
    uint32_t tmp = nondet_status();

    if (STATUS_SUCCESS != retval || ERROR_INVALID_STATUS == tmp)
    {
        if (STATUS_SUCCESS == retval)
        {
            retval = ERROR_INVALID_STATUS;
        }

        *status = ERROR_INVALID_STATUS;
        goto done;
    }
    else
    {
        *status = tmp;
        goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_append_response),
        retval, status);

    return retval;
}
