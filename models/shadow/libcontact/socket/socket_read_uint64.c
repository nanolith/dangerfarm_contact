#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

int nondet_status();
uint64_t nondet_uint64();

int DANGERFARM_CONTACT_SYM(socket_read_uint64)(uint64_t* val, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_uint64), val, s);

    int retval;

    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(s));

    *val = nondet_uint64();

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        retval = STATUS_SUCCESS;
        goto done;
    }
    else
    {
        *val = 0;
        retval = ERROR_SOCKET_READ;
        goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_uint64), retval, val);

    return retval;
}
