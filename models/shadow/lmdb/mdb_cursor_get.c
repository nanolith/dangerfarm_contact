#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stdlib.h>

#include "lmdb_internal.h"

int nondet_retval();

int mdb_cursor_get(
    MDB_cursor* cursor, MDB_val* key, MDB_val* data, MDB_cursor_op op)
{
    MODEL_ASSERT(prop_MDB_cursor_valid(cursor));
    MODEL_ASSERT(NULL != key);
    MODEL_ASSERT(NULL != key->mv_data);
    const uint8_t* bkdata = (const uint8_t*)key->mv_data;
    MODEL_ASSERT(bkdata[0] == bkdata[0]);
    MODEL_ASSERT(bkdata[key->mv_size - 1] == bkdata[key->mv_size - 1]);
    MODEL_ASSERT(NULL != data);
    MODEL_ASSERT(MDB_FIRST == op || MDB_NEXT == op);

    int retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        key->mv_data = cursor->key_buffer;
        key->mv_size = cursor->key_buffer_size;
        data->mv_data = cursor->txn->data_buffer;
        data->mv_size = cursor->txn->data_buffer_size;
        return STATUS_SUCCESS;
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
