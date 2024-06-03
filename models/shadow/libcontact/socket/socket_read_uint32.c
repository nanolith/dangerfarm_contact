#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

int nondet_status();
uint32_t nondet_uint32();

int socket_read_uint32(uint32_t* val, int s)
{
    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(s));

    /* prove access by writing a nondet value to val. */
    /* also, this covers partial read scenarios from read(). */
    *val = nondet_uint32();

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        return STATUS_SUCCESS;
    }
    else
    {
        return ERROR_SOCKET_READ;
    }
}
