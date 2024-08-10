#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stdlib.h>

#include "lmdb_internal.h"

int nondet_retval();
int nondet_descriptor();

int mdb_dbi_open(
    MDB_txn* txn, const char* name, unsigned int flags, MDB_dbi* dbi)
{
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    MODEL_ASSERT(NULL != name);
    MODEL_ASSERT(NULL != dbi);
    MODEL_ASSERT(txn->env->dbi_count > 0);

    /* does this function succeed? */
    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
            break;

        case MDB_NOTFOUND:
        case MDB_DBS_FULL:
            return retval;

        default:
            return MDB_NOTFOUND;
    }

    /* success. */
    ++txn->dbi_count;
    *dbi = nondet_descriptor();
    return STATUS_SUCCESS;
}
