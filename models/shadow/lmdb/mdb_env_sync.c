#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>

#include "lmdb_internal.h"

int nondet_retval();

int mdb_env_sync(MDB_env* env, int force)
{
    MODEL_ASSERT(prop_MDB_env_opened(env));

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
        case EACCES:
        case EINVAL:
        case EIO:
            return retval;

        default:
            return EIO;
    }
}
