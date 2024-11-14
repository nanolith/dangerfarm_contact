#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();
uint32_t nondet_status();
size_t nondet_count();

/* cap size at 1000 entries. */
size_t compute_size()
{
    size_t retval = nondet_count();

    if (retval > 1000)
    {
        retval = 1000;
    }

    return retval;
}

int DANGERFARM_CONTACT_SYM(database_read_contact_form_list_response)(
    uint32_t* status, uint64_t* count, uint64_t** id_list, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_list_response),
        status, count, id_list, s);

    /* determine the return value. */
    int retval = nondet_retval();
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* determine the status. */
    *status = nondet_status();
    if (ERROR_INVALID_STATUS == *status)
    {
        retval = ERROR_INVALID_STATUS;
        goto clear_count;
    }

    /* did the status fail? */
    if (STATUS_SUCCESS != *status)
    {
        goto clear_count;
    }

    /* get the count. */
    *count = compute_size();

    /* allocate memory for the list. */
    *id_list = (uint64_t*)malloc(sizeof(uint64_t) * (*count));
    if (NULL == *id_list)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto fail;
    }

    /* ensure that the contents of this list are non-deterministic. */
    uint64_t contents_nondet[*count];
    __CPROVER_array_replace((uint64_t*)*id_list, contents_nondet);

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *status = ERROR_INVALID_STATUS;

clear_count:
    *count = 0;
    *id_list = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_list_response),
        retval, status, count, id_list);

    return retval;
}
