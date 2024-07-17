#include <dangerfarm_contact/status_codes.h>
#include <unistd.h>

#ifdef __FreeBSD__
#include <sys/capsicum.h>
#endif

#include "contactdb_internal.h"

/**
 * \brief Drop privileges to only those needed for database communication.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_drop_privileges(contactdb_context* ctx)
{
    int retval;

    (void)ctx;
    (void)retval;

    #ifdef __FreeBSD__
    retval = cap_enter();
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CONTACTDB_DROP_PRIVILEGES;
    }
    #endif

    #ifdef __OpenBSD__
    retval = pledge("flock error stdio unix", "");
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CONTACTDB_DROP_PRIVILEGES;
    }
    #endif

    /* by default, return success. */
    return STATUS_SUCCESS;
}
