#include "contactdb_internal.h"

/**
 * \brief Confirm whether the given capability exists in this context.
 *
 * \param ctx           The context to check.
 * \param cap           The capability to check against.
 *
 * \returns true if the contactdb has this capability, and false otherwise.
 */
bool contactdb_has_capability(const contactdb_context* ctx, const uint64_t cap)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_has_capability, ctx, cap);

    bool retval;

    if ((ctx->root_capabilities & cap) == cap)
    {
        retval = true;
        goto done;
    }

    retval = false;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(contactdb_has_capability, retval);

    return retval;
}
