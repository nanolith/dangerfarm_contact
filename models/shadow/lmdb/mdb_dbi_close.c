#include <dangerfarm_contact/cbmc/model_assert.h>

#include "lmdb_internal.h"

void mdb_dbi_close(MDB_env *env, MDB_dbi dbi)
{
    MODEL_ASSERT(prop_MDB_env_opened(env));
    MODEL_ASSERT(env->dbi_alloc_count > 0);

    --(env->dbi_alloc_count);
}
