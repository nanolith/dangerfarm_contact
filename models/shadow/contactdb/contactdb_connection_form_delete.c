#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../lmdb/lmdb_internal.h"

int nondet_retval();

int contactdb_connection_form_delete(
    contactdb_connection* conn, MDB_txn* txn, uint64_t id)
{
    MODEL_ASSERT(prop_is_valid_contactdb_connection(conn));
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    MODEL_ASSERT(prop_MDB_dbi_valid(conn->env, conn->global_db));

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
            return STATUS_SUCCESS;

        case ERROR_DATABASE_GET:
        case ERROR_CONTACTDB_GET_INVALID_SIZE:
            return retval;
    }
}
