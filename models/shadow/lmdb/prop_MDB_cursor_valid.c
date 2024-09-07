#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stddef.h>

#include "lmdb_internal.h"

bool prop_MDB_cursor_valid(const MDB_cursor* cursor)
{
    MODEL_ASSERT(NULL != cursor);

    return
        prop_MDB_txn_valid(cursor->txn)
     && prop_MDB_dbi_valid(cursor->txn->env, cursor->dbi);
}
