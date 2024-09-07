#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stdlib.h>

#include "lmdb_internal.h"

int nondet_retval();
size_t nondet_size();

size_t key_size()
{
    size_t retval = nondet_size();

    if (retval > 100)
    {
        retval = 100;
    }

    return retval;
}

size_t result_count()
{
    size_t retval = nondet_size();

    if (retval > 3)
    {
        retval = 3;
    }

    return retval;
}

int mdb_cursor_open(MDB_txn* txn, MDB_dbi dbi, MDB_cursor** cursor)	
{
    /* the transaction must be valid. */
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    /* the dbi must be valid. */
    MODEL_ASSERT(prop_MDB_dbi_valid(txn->env, dbi));

    /* does this operation succeed? */
    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
            break;

        case EINVAL:
        case ENOMEM:
            return retval;

        default:
            return ENOMEM;
    }

    /* allocate memory for this cursor. */
    *cursor = malloc(sizeof(MDB_cursor));
    if (NULL == *cursor)
    {
        return ENOMEM;
    }

    /* allocate memory for the key buffer. */
    size_t key_buffer_size = key_size();
    void* key = malloc(key_buffer_size);
    if (NULL == key)
    {
        free(*cursor);
        return ENOMEM;
    }

    (*cursor)->key_buffer = (uint8_t*)key;
    (*cursor)->key_buffer_size = key_buffer_size;
    (*cursor)->txn = txn;
    (*cursor)->dbi = dbi;
    (*cursor)->count = result_count();

    /* success. */
    return STATUS_SUCCESS;
}
