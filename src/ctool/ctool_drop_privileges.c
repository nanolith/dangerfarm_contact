#include <dangerfarm_contact/status_codes.h>
#include <unistd.h>

#ifdef __FreeBSD__
#include <sys/capsicum.h>
#endif

#include "ctool_internal.h"

/**
 * \brief Drop privileges before communicating with the database.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_drop_privileges(ctool_context* ctx)
{
    int retval;

    (void)ctx;
    (void)retval;

    #ifdef __FreeBSD__
    retval = cap_enter();
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CTOOL_DROP_PRIVILEGES;
    }
    #endif

    #ifdef __OpenBSD__
    retval = pledge("stdio", "");
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CTOOL_DROP_PRIVILEGES;
    }
    #endif

    /* by default, return success. */
    return STATUS_SUCCESS;
}
