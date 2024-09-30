#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

int nondet_status();

int DANGERFARM_CONTACT_SYM(socket_write_uint32)(int s, uint32_t val)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_write_uint32), s, val);

    int retval;

    /* does this write succeed? */
    if (0 == nondet_status())
    {
        retval = STATUS_SUCCESS;
        goto done;
    }
    else
    {
        retval = ERROR_SOCKET_WRITE;
        goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_write_uint32), retval);

    return retval;
}
