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
    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(s));

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        char contents_nondet[size];
        __CPROVER_array_replace((char*)data, contents_nondet);

        return STATUS_SUCCESS;
    }
    else
    {
        return ERROR_SOCKET_READ;
    }
}
