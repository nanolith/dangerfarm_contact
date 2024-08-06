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
        return 1;
    }

    /* close the MDB environment. */
    mdb_env_close(env);

    return 0;
}
