#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>

#include "lmdb_internal.h"

int retval_nondet();

int mdb_env_set_mapsize(MDB_env *env, mdb_size_t size)
{
    MODEL_ASSERT(prop_MDB_env_created(env));

    int retval = retval_nondet();
    switch (retval)
    {
        case EINVAL:
        case STATUS_SUCCESS:
            return retval;

        default:
            return EINVAL;
    }
}
