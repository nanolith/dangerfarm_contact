#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../lmdb/lmdb_internal.h"

int nondet_retval();

int contactdb_connection_form_delete(
    contactdb_connection* conn, MDB_txn* txn, uint64_t id)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_delete, conn, txn, id);

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
        case ERROR_DATABASE_GET:
        case ERROR_CONTACTDB_GET_INVALID_SIZE:
            goto done;

        default:
            retval = ERROR_DATABASE_GET;
            goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_form_delete, retval);

    return retval;
}
