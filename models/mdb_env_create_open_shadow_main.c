#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <lmdb.h>

#include "shadow/lmdb/lmdb_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    MDB_env* env;

    /* Create the MDB environment. */
    retval = mdb_env_create(&env);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* the database is created, but not opened. */
    MODEL_ASSERT(prop_MDB_env_created(env));
    MODEL_ASSERT(!prop_MDB_env_opened(env));

    int flags = 0;
    #ifdef __OpenBSD__
    flags |= MDB_WRITEMAP;
    #endif

    /* attempt to open the database. */
    retval = mdb_env_open(env, "path/to/db", flags, 0600);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto close_env;
    }

    /* if we've made it this far, the database is opened. */
    MODEL_ASSERT(prop_MDB_env_opened(env));

    /* success. */
    retval = 0;
    goto close_env;

close_env:
    /* close the MDB environment. */
    mdb_env_close(env);

done:
    return retval;
}
