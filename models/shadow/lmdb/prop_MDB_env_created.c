#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stddef.h>

#include "lmdb_internal.h"

bool prop_MDB_env_created(const MDB_env* env)
{
    MODEL_ASSERT(NULL != env);

    return env->created;
}
