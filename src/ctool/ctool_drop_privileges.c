#include <dangerfarm_contact/status_codes.h>

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
    (void)ctx;

    /* by default, return success. */
    return STATUS_SUCCESS;
}
