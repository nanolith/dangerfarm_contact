#include <dangerfarm_contact/protocol/database.h>

#include "../../data/contact_form_shadow.h"

int nondet_retval();
int nondet_status();

int DANGERFARM_CONTACT_SYM(database_read_contact_form_read_response)(
    uint32_t* status, DANGERFARM_CONTACT_SYM(contact_form)** form, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_read_response),
        status, form, s);

    /* does this fail? */
    int retval = nondet_retval();
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* get the status. */
    *status = nondet_status();

    /* if the status is ERROR_INVALID_STATUS, then this is an error. */
    if (ERROR_INVALID_STATUS == *status)
    {
        retval = ERROR_INVALID_STATUS;
        goto fail;
    }

    /* only read the payload if the status is successful. */
    if (STATUS_SUCCESS != *status)
    {
        goto clear_form;
    }

    /* build the contact form data. */
    retval = contact_form_create_nondet(form);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *status = ERROR_INVALID_STATUS;

clear_form:
    *form = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_read_response),
        retval, status, form);

    return retval;
}
