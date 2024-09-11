#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stdlib.h>

#include "lmdb_internal.h"

int nondet_retval();

int mdb_txn_commit(MDB_txn *txn)
{
    MODEL_ASSERT(prop_MDB_txn_valid(txn));

    /* does this operation succeed? */
    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
            break;

        case EINVAL:
        case ENOSPC:
        case EIO:
        case ENOMEM:
            return retval;

        default:
            return EIO;
    }

    /* reset transaction state if the transaction isn't nested. */
    if (NULL == txn->parent)
    {
        txn->env->in_txn = false;
        txn->env->txn = NULL;
    }

    /* update DBI counts based on transaction commit. */
    txn->env->dbi_count -= txn->dbi_count;
    txn->env->dbi_alloc_count += txn->dbi_count;

    if (NULL != txn->data_buffer)
    {
        free(txn->data_buffer);
    }

    if (NULL != txn->temp_object)
    {
        free(txn->temp_object);
    }

    free(txn);

    return STATUS_SUCCESS;
}
