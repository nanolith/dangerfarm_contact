#include <stddef.h>

#include "contactdb_internal.h"

/**
 * \brief Disable the signal handler.
 *
 * \param ctx           The context to use for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_disable_signal_handler(contactdb_context* ctx)
{
    (void)ctx;

    return contactdb_install_signal_handler(NULL);
}
