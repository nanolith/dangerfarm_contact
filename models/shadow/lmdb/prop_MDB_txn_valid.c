#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stddef.h>

#include "lmdb_internal.h"

bool prop_MDB_txn_valid(const MDB_env* env, const MDB_txn* txn)
{
    MODEL_ASSERT(prop_MDB_env_opened(env));

    if (NULL != txn->parent)
    {
        return prop_MDB_txn_valid(env, txn->parent);
    }
    else
    {
        MODEL_ASSERT(prop_MDB_env_in_txn(env));
        MODEL_ASSERT(env->txn == txn);

        return true;
    }
}
