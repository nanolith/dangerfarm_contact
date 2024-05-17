#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

int nondet_status();

int socket_write_uint64(int s, uint64_t val)
{
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
