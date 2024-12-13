#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>

#include "lmdb_internal.h"

int nondet_retval();

int mdb_env_set_mapsize(MDB_env *env, size_t size)
{
    MODEL_ASSERT(prop_MDB_env_created(env));
    MODEL_ASSERT(!prop_MDB_env_opened(env));
    MODEL_ASSERT(!prop_MDB_env_in_txn(env));

    int retval = nondet_retval();
    switch (retval)
    {
        case EINVAL:
        case STATUS_SUCCESS:
            return retval;

        default:
            return EINVAL;
    }
}
