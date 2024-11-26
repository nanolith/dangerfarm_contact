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
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_disable_signal_handler, ctx);

    (void)ctx;

    int retval = contactdb_install_signal_handler(NULL);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_disable_signal_handler, retval);

    return retval;
}
