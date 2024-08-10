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
    MDB_dbi dbi = 0;
    bool dbi_opened = false;

    /* Create the MDB environment. */
    retval = mdb_env_create(&env);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* we need one database handle. */
    retval = mdb_env_set_maxdbs(env, 1);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_env;
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

    /* begin a transaction. */
    retval = mdb_txn_begin(env, NULL, 0, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_env;
    }

    /* open a database descriptor. */
    retval = mdb_dbi_open(txn, "foo.db", 0, &dbi);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto txn_abort;
    }

    /* commit the transaction. */
    retval = mdb_txn_commit(txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto txn_abort;
    }

    /* success. */
    retval = 0;
    dbi_opened = true;
    goto close_dbi;

txn_abort:
    mdb_txn_abort(txn);

close_dbi:
    if (dbi_opened)
    {
        mdb_dbi_close(env, dbi);
    }

cleanup_env:
    mdb_env_close(env);

done:
    return retval;
}
