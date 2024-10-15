#include <dangerfarm_contact/status_codes.h>

#include <lmdb.h>

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

    /* set the max DBs. */
    retval = mdb_env_set_maxdbs(env, 5);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_env;
    }

    /* success. */
    retval = 0;
    goto cleanup_env;

cleanup_env:
    mdb_env_close(env);

done:
    return retval;
}
