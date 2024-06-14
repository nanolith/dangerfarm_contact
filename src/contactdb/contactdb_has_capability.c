#include "contactdb_internal.h"

/**
 * \brief Confirm whether the given capability exists in this context.
 *
 * \brief ctx           The context to check.
 * \brief cap           The capability to check against.
 */
bool contactdb_has_capability(const contactdb_context* ctx, const uint64_t cap)
{
    if ((ctx->root_capabilities & cap) == cap)
    {
        return true;
    }

    return false;
}
