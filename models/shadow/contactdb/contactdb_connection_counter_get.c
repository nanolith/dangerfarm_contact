#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../lmdb/lmdb_internal.h"

int nondet_retval();

uint64_t nondet_value();

uint64_t pick_counter_value()
{
    uint64_t retval = nondet_value();

    MODEL_ASSUME(COUNTER_VALUE_INVALID != retval);

    return retval;
}

int contactdb_connection_counter_get(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_counter_get, conn, txn, counter_id, value);

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
            *value = pick_counter_value();
            retval = STATUS_SUCCESS;
            goto done;

        case ERROR_DATABASE_GET:
        case ERROR_CONTACTDB_GET_INVALID_SIZE:
            goto fail;

        default:
            retval = ERROR_DATABASE_GET;
            goto fail;
    }

fail:
    *value = COUNTER_VALUE_INVALID;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_counter_get_and_decrement, retval, value);

    return retval;
}
