#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stddef.h>

#include "lmdb_internal.h"

static uint8_t returned_data[100];

int nondet_retval();
size_t nondet_size();

size_t random_size(size_t max)
{
    size_t retval = nondet_size();
    if (retval > max)
    {
        retval = max;
    }

    return retval;
}

int mdb_get(MDB_txn* txn, MDB_dbi dbi, MDB_val* key, MDB_val* data)
{
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    MODEL_ASSERT(prop_MDB_dbi_valid(txn->env, dbi));
    MODEL_ASSERT(NULL != key);
    MODEL_ASSERT(NULL != data);
    MODEL_ASSERT(NULL != key->mv_data);
    MODEL_ASSERT(key->mv_size > 0);
    const uint8_t* bkdata = (const uint8_t*)key->mv_data;
    MODEL_ASSERT(bkdata[0] == bkdata[0]);
    MODEL_ASSERT(bkdata[key->mv_size - 1] == bkdata[key->mv_size - 1]);

    int retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        data->mv_data = returned_data;
        data->mv_size = random_size(sizeof(returned_data));
    }
    else
    {
        switch (retval)
        {
            case MDB_NOTFOUND:
            case EINVAL:
                return retval;

            default:
                return MDB_NOTFOUND;
        }
    }
}
