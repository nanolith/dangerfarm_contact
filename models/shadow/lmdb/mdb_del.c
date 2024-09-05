#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stddef.h>

#include "lmdb_internal.h"

int nondet_retval();

int mdb_del(MDB_txn* txn, MDB_dbi dbi, MDB_val* key, MDB_val* data)
{
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    MODEL_ASSERT(prop_MDB_dbi_valid(txn->env, dbi));
    MODEL_ASSERT(NULL != key);
    MODEL_ASSERT(NULL == data);
    MODEL_ASSERT(NULL != key->mv_data);
    MODEL_ASSERT(key->mv_size > 0);
    const uint8_t* bkdata = (const uint8_t*)key->mv_data;
    MODEL_ASSERT(bkdata[0] == bkdata[0]);
    MODEL_ASSERT(bkdata[key->mv_size - 1] == bkdata[key->mv_size - 1]);

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
        case MDB_NOTFOUND:
        case EINVAL:
        case EACCES:
            return retval;

        default:
            return MDB_NOTFOUND;
    }
}
