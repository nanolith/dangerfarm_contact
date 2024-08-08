#include <dangerfarm_contact/status_codes.h>
#include <lmdb.h>
#include <stddef.h>

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

    /* begin a transaction. */
    retval = mdb_txn_begin(env, NULL, 0, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_env;
    }

    /* abort the transaction. */
    mdb_txn_abort(txn);

    /* success. */
    retval = 0;
    goto cleanup_env;

cleanup_env:
    mdb_env_close(env);

done:
    return retval;
}
