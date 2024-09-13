#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../lmdb/lmdb_internal.h"

int nondet_retval();

uint64_t nondet_value();

uint64_t counter_value()
{
    uint64_t retval = nondet_value();
    if (retval > 5)
    {
        retval = 5;
    }

    return retval;
}

int contactdb_connection_counter_get(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value)
{
    MODEL_ASSERT(prop_is_valid_contactdb_connection(conn));
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    MODEL_ASSERT(prop_MDB_dbi_valid(conn->env, conn->global_db));
    MODEL_ASSERT(counter_id == COUNTER_ID_CONTACT_COUNT);
    MODEL_ASSERT(NULL != value);

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
            *value = counter_value();
            return STATUS_SUCCESS;

        case ERROR_DATABASE_GET:
        case ERROR_CONTACTDB_GET_INVALID_SIZE:
            return retval;
    }
}
