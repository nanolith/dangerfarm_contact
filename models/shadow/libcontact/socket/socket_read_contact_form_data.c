#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

int nondet_status();
char nondet_char();

int DANGERFARM_CONTACT_SYM(socket_read_contact_form_data)(
    char* data, int s, size_t size)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_contact_form_data), data, s, size);

    int retval;

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        char contents_nondet[size];
        __CPROVER_array_replace((char*)data, contents_nondet);

        retval = STATUS_SUCCESS;
        goto done;
    }
    else
    {
        retval = ERROR_SOCKET_READ;
        goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_contact_form_data), retval);

    return retval;
}
