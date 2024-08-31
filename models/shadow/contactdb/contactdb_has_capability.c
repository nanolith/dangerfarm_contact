#include <stdbool.h>

#include "../../../src/contactdb/contactdb_internal.h"

bool nondet_bool();

bool contactdb_has_capability(const contactdb_context* ctx, const uint64_t cap)
{
    return nondet_bool();
}
