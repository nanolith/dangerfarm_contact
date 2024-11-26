#include <stdbool.h>

#include "../../../src/contactdb/contactdb_internal.h"

bool nondet_bool();

bool contactdb_has_capability(const contactdb_context* ctx, const uint64_t cap)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_has_capability, ctx, cap);

    bool retval = nondet_bool();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(contactdb_has_capability, retval);

    return retval;
}
