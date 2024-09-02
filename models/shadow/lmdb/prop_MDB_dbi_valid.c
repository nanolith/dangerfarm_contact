#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stddef.h>

#include "lmdb_internal.h"

bool prop_MDB_dbi_valid(const MDB_env* env, MDB_dbi dbi)
{
    MODEL_ASSERT(NULL != env);

    return dbi < env->dbi_alloc_count;
}
