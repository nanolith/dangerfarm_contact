#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stdlib.h>

#include "lmdb_internal.h"

void mdb_txn_abort(MDB_txn *txn)
{
    MODEL_ASSERT(prop_MDB_txn_valid(txn));

    if (NULL == txn->parent)
    {
        txn->env->in_txn = false;
        txn->env->txn = NULL;
    }

    if (NULL != txn->data_buffer)
    {
        free(txn->data_buffer);
    }

    if (NULL != txn->temp_object)
    {
        free(txn->temp_object);
    }

    free(txn);
}
