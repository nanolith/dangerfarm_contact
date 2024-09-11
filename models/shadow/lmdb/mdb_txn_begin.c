#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stdlib.h>

#include "lmdb_internal.h"

int nondet_retval();
size_t nondet_size();

size_t buff_size()
{
    size_t retval = nondet_size();

    if (retval > 100)
    {
        retval = 100;
    }

    return retval;
}

int mdb_txn_begin(
    MDB_env* env, MDB_txn* parent, unsigned int flags, MDB_txn** txn)
{
    /* the database must be opened for transactions. */
    MODEL_ASSERT(prop_MDB_env_opened(env));

    /* if there is a parent transaction... */
    if (NULL != parent)
    {
        /* it must be valid. */
        MODEL_ASSERT(prop_MDB_txn_valid(parent));
    }
    else
    {
        /* otherwise, the environment must not be in a transaction. */
        MODEL_ASSERT(!prop_MDB_env_in_txn(env));
    }

    /* does this operation succeed? */
    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
            break;

        case MDB_PANIC:
        case MDB_MAP_RESIZED:
        case MDB_READERS_FULL:
        case ENOMEM:
            return retval;

        default:
            return ENOMEM;
    }

    /* allocate memory for this transaction. */
    *txn = malloc(sizeof(MDB_txn));
    if (NULL == *txn)
    {
        return ENOMEM;
    }

    /* allocate memory for the data buffer. */
    size_t buffer_size = buff_size();
    void* buffer = malloc(buffer_size);
    if (NULL == buffer)
    {
        free(*txn);
        return ENOMEM;
    }

    (*txn)->data_buffer = (uint8_t*)buffer;
    (*txn)->data_buffer_size = buffer_size;
    (*txn)->env = env;
    (*txn)->parent = parent;
    (*txn)->flags = flags;
    (*txn)->dbi_count = 0;
    (*txn)->temp_object = NULL;
    env->txn = *txn;
    env->in_txn = true;

    /* success. */
    return STATUS_SUCCESS;
}
