#include <dangerfarm_contact/cbmc/model_assert.h>

#include "lmdb_internal.h"

void mdb_env_close(MDB_env* env)
{
    MODEL_ASSERT(prop_MDB_env_created(env));

    free(env);
}
