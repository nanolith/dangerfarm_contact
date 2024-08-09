#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>

#include "lmdb_internal.h"

int nondet_retval();

int mdb_env_set_maxdbs(MDB_env *env, MDB_dbi dbs)
{
    MODEL_ASSERT(prop_MDB_env_created(env));
    MODEL_ASSERT(!prop_MDB_env_opened(env));
    MODEL_ASSERT(!prop_MDB_env_in_txn(env));

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
            env->dbi_count = dbs;
            return retval;

        case EINVAL:
        default:
            return EINVAL;
    }
}
