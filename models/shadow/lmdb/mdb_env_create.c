#include <dangerfarm_contact/cbmc/model_assert.h>
#include <string.h>

#include "lmdb_internal.h"

int mdb_env_create(MDB_env** env)
{
    MODEL_ASSERT(NULL != env);

    *env = malloc(sizeof(MDB_env));
    if (NULL == *env)
    {
        return MDB_PROBLEM;
    }

    memset(*env, 0, sizeof(MDB_env));
    (*env)->created = true;

    return MDB_SUCCESS;
}
