#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

int nondet_status();
uint32_t nondet_uint32();

int DANGERFARM_CONTACT_SYM(socket_read_uint32)(uint32_t* val, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_uint32), val, s);

    int retval;

    *val = nondet_uint32();

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
        DANGERFARM_CONTACT_SYM(socket_read_uint32), retval, val);

    return retval;
}
