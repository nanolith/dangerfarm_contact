#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stddef.h>

#include "lmdb_internal.h"

bool prop_MDB_txn_valid(const MDB_txn* txn)
{
    MODEL_ASSERT(NULL != txn);
    MODEL_ASSERT(prop_MDB_env_opened(txn->env));

    if (NULL != txn->parent)
    {
        MODEL_ASSERT(txn->parent->env == txn->env);
        return prop_MDB_txn_valid(txn->parent);
    }
    else
    {
        MODEL_ASSERT(prop_MDB_env_in_txn(txn->env));
        MODEL_ASSERT(txn->env->txn == txn);

        return true;
    }
}
