#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

#include "contact_form_shadow.h"
#include "../../unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

int nondet_status();

int DANGERFARM_CONTACT_SYM(contact_form_read)(
    DANGERFARM_CONTACT_SYM(contact_form)** form, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_read), form, s);

    int retval;

    /* does this read fail? */
    if (0 != nondet_status())
    {
        *form = NULL;
        retval = ERROR_SOCKET_READ;
        goto done;
    }

    retval = contact_form_create_nondet(form);
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_read), retval, form);

    return retval;
}
