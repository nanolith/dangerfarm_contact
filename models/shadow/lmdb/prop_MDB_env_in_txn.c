#include <dangerfarm_contact/cbmc/model_assert.h>

#include "lmdb_internal.h"

bool prop_MDB_env_in_txn(const MDB_env* env);
{
    MODEL_ASSERT(NULL != env);

    return env->in_txn;
}
