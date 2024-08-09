#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <lmdb.h>
#include <stddef.h>

#include "shadow/lmdb/lmdb_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    MDB_env* env;
    MDB_txn* txn;

    /* Create the MDB environment. */
    retval = mdb_env_create(&env);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    int flags = 0;
    #ifdef __OpenBSD__
    flags |= MDB_WRITEMAP;
    #endif

    /* attempt to open the database. */
    retval = mdb_env_open(env, "path/to/db", flags, 0600);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_env;
    }

    /* we are not currently in a transaction. */
    MODEL_ASSERT(!prop_MDB_env_in_txn(env));

    /* begin a transaction. */
    retval = mdb_txn_begin(env, NULL, 0, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_env;
    }

    /* we are in a transaction. */
    MODEL_ASSERT(prop_MDB_env_in_txn(env));

    /* abort the transaction. */
    mdb_txn_abort(txn);

    /* we are no longer in a transaction. */
    MODEL_ASSERT(!prop_MDB_env_in_txn(env));

    /* success. */
    retval = 0;
    goto cleanup_env;

cleanup_env:
    mdb_env_close(env);

done:
    return retval;
}
