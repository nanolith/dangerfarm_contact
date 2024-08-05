#include <dangerfarm_contact/cbmc/model_assert.h>

#include "lmdb_internal.h"

int mdb_env_create(MDB_env** env)
{
    MODEL_ASSERT(NULL != env);

    *env = malloc(sizeof(MDB_env));
    if (NULL == *env)
    {
        return MDB_PROBLEM;
    }

    (*env)->created = true;
    (*env)->opened = false;
    (*env)->in_txn = false;
    (*env)->dbi_count = 0;

    return MDB_SUCCESS;
}
