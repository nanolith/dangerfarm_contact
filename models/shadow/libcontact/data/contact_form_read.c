#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

#include "contact_form_shadow.h"
#include "../../unix/unix_shadow.h"

int nondet_status();

int contact_form_read(contact_form** form, int s)
{
    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(s));

    /* does this read fail? */
    if (0 != nondet_status())
    {
        return ERROR_SOCKET_READ;
    }

    return contact_form_create_nondet(form, NULL, NULL, NULL, NULL);
}
