#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

#include "../../unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

int nondet_status();

int DANGERFARM_CONTACT_SYM(contact_form_write)(
    int s, const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_write), s, form);

    int retval;

    /* does this write succeed? */
    if (0 == nondet_status())
    {
        retval = STATUS_SUCCESS;
        goto done;
    }
    else
    {
        retval = ERROR_SOCKET_WRITE;
        goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_write), retval);

    return retval;
}
