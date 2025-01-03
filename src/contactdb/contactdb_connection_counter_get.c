#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "contactdb_connection.h"

/**
 * \brief Given a connection and a transaction, read the current counter but DO
 * NOT INCREMENT IT.
 *
 * \note If the counter is not found, this method will return 0.
 *
 * \param conn          The connection for this operation.
 * \param txn           The transaction for this operation.
 * \param counter_id    The counter id for this operation.
 * \param value         Pointer to receive the counter on success.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_connection_counter_get(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_counter_get, conn, txn, counter_id, value);

    int retval;
    MDB_val key, val;

    /* set up the key for the transaction. */
    key.mv_size = sizeof(counter_id);
    key.mv_data = &counter_id;

    /* get this value from the database. */
    retval = mdb_get(txn, conn->global_db, &key, &val);
    if (MDB_NOTFOUND == retval)
    {
        *value = 0;
        retval = STATUS_SUCCESS;
        goto done;
    }
    else if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_GET;
        goto fail;
    }

    /* verify that the returned size of this data is correct. */
    if (val.mv_size != sizeof(*value))
    {
        retval = ERROR_CONTACTDB_GET_INVALID_SIZE;
        goto fail;
    }

    /* save the value. */
    memcpy(value, val.mv_data, val.mv_size);

    /* if the value is invalid, this is an error. */
    if (COUNTER_VALUE_INVALID == *value)
    {
        retval = ERROR_CONTACTDB_BAD_COUNTER_VALUE;
        goto fail;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *value = COUNTER_VALUE_INVALID;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_counter_get_and_decrement, retval, value);

    return retval;
}
