#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

int nondet_status();
char nondet_char();

int socket_read_contact_form_data(char* data, int s, size_t size)
{
    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(s));

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        size_t shadow_size = size;
        if (shadow_size > 9)
        {
            shadow_size = 9;
        }

        for (size_t i = 0; i < shadow_size; ++i)
        {
            data[i] = nondet_char();
        }
        return STATUS_SUCCESS;
    }
    else
    {
        return ERROR_SOCKET_READ;
    }
}
