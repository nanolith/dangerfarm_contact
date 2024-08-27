#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "../../../src/contactdb/contactdb_connection.h"

int nondet_retval();

int contactdb_connection_create(contactdb_connection** conn, const char* path)
{
    MODEL_ASSERT(NULL != conn);
    MODEL_ASSERT(NULL != path);

    int retval = nondet_retval();
    switch (retval)
    {
        case ERROR_GENERAL_OUT_OF_MEMORY:
        case ERROR_DATABASE_ENV_CREATE:
        case ERROR_DATABASE_SET_MAPSIZE:
        case ERROR_DATABASE_SET_MAXDBS:
        case ERROR_DATABASE_ENV_OPEN:
        case ERROR_DATABASE_TXN_BEGIN:
        case ERROR_DATABASE_DBI_OPEN:
        case ERROR_DATABASE_TXN_COMMIT:
        case STATUS_SUCCESS:
            return retval;

        default:
            return ERROR_GENERAL_OUT_OF_MEMORY;
    }
}
