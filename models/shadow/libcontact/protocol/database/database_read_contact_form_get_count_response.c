#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>

int nondet_retval();
uint32_t nondet_status();
uint64_t nondet_count();

int DANGERFARM_CONTACT_SYM(database_read_contact_form_get_count_response)(
    uint32_t* status, uint64_t* count, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_get_count_response),
        status, count, s);

    int retval = nondet_retval();
    uint32_t tmp = nondet_status();

    if (STATUS_SUCCESS != retval || ERROR_INVALID_STATUS == tmp)
    {
        if (STATUS_SUCCESS == retval)
        {
            retval = ERROR_INVALID_STATUS;
        }

        *count = 0;
        *status = ERROR_INVALID_STATUS;
        goto done;
    }
    else if (STATUS_SUCCESS == tmp)
    {
        *status = tmp;
        *count = nondet_count();
        goto done;
    }
    else
    {
        *status = tmp;
        *count = 0;
        goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_get_count_response),
        retval, status, count);

    return retval;
}
