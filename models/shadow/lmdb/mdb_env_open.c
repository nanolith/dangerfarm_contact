#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stddef.h>

#include "lmdb_internal.h"

int retval_nondet();

int mdb_env_open(
    MDB_env *env, const char *path, unsigned int flags, mdb_mode_t mode)
{
    MODEL_ASSERT(prop_MDB_env_created(env));
    MODEL_ASSERT(NULL != path);
#ifdef __OpenBSD__
    MODEL_ASSERT(MDB_WRITEMAP == flags)
#else
    MODEL_ASSERT(0 == flags);
#endif
    MODEL_ASSERT(0600 == mode);

    int retval = retval_nondet();
    switch (retval)
    {
        case STATUS_SUCCESS:
            env->opened = true;
            return retval;

        case MDB_VERSION_MISMATCH:
        case MDB_INVALID:
        case ENOENT:
        case EACCES:
        case EAGAIN:
            return retval;

        default:
            return MDB_INVALID;
    }
}
