#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

#include "../../unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

int nondet_status();

int DANGERFARM_CONTACT_SYM(contact_form_write)(
    int s, const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    /* verify that this is a valid contact form. */
    MODEL_ASSERT(prop_valid_contact_form(form));

    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(s));

    /* does this write succeed? */
    if (0 == nondet_status())
    {
        return STATUS_SUCCESS;
    }
    else
    {
        return ERROR_SOCKET_WRITE;
    }
}
