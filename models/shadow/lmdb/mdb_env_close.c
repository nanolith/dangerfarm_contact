#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stdlib.h>

#include "lmdb_internal.h"

void mdb_env_close(MDB_env* env)
{
    MODEL_ASSERT(prop_MDB_env_created(env));
    MODEL_ASSERT(!prop_MDB_env_in_txn(env));
    MODEL_ASSERT(0 == env->dbi_alloc_count);

    free(env);
}
