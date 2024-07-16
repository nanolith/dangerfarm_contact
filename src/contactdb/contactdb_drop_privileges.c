#include <dangerfarm_contact/status_codes.h>
#include <unistd.h>

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

    /* by default, return success. */
    return STATUS_SUCCESS;
}
