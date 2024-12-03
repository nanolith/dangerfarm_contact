#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "contactdb_connection.h"

/* forward decls. */
static int get_counter_value(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value);
static int put_counter_value(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t value);

/**
 * \brief Given a connection and a transaction, read and increment the given
 * counter id, returning the result.
 *
 * \note If the counter is not found, it will be set to 1 and saved in the
 * database.
 *
 * \param conn          The connection for this operation.
 * \param txn           The transaction for this operation.
 * \param counter_id    The counter id for this operation.
 * \param value         Pointer to receive the incremented counter on success.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_connection_counter_get_and_increment(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_counter_get_and_increment,
        conn, txn, counter_id, value);

    int retval;
    uint64_t local_value = 0;

    /* attempt to get the counter value. */
    retval = get_counter_value(conn, txn, counter_id, &local_value);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* increment this value. */
    local_value += 1;

    /* attempt to put the counter value. */
    retval = put_counter_value(conn, txn, counter_id, local_value);
    if (STATUS_SUCCESS != retval)
    {
        goto fail;
    }

    /* is the value invalid? */
    if (COUNTER_VALUE_INVALID == local_value)
    {
        retval = ERROR_CONTACTDB_BAD_COUNTER_VALUE;
        goto fail;
    }

    /* Success. Set the output value. */
    *value = local_value;
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *value = COUNTER_VALUE_INVALID;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_counter_get_and_increment, retval, value);

    return retval;
}

/**
 * \brief Read the counter value from the database, setting the value to 0 if it
 * is unset.
 *
 * \param conn          The connection for this operation.
 * \param txn           The transaction for this operation.
 * \param counter_id    The counter id for this operation.
 * \param value         Pointer to receive the value on success.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int get_counter_value(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value)
{
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
        return STATUS_SUCCESS;
    }
    else if (STATUS_SUCCESS != retval)
    {
        return ERROR_DATABASE_GET;
    }

    /* verify that the returned size of this data is correct. */
    if (val.mv_size != sizeof(*value))
    {
        return ERROR_CONTACTDB_GET_INVALID_SIZE;
    }

    /* save the value. */
    memcpy(value, val.mv_data, val.mv_size);

    /* success. */
    return STATUS_SUCCESS;
}

/**
 * \brief Write the counter value to the database.
 *
 * \param conn          The connection for this operation.
 * \param txn           The transaction for this operation.
 * \param counter_id    The counter id for this operation.
 * \param value         The value to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int put_counter_value(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t value)
{
    int retval;
    MDB_val key, val;

    /* set up the key / value for writing. */
    key.mv_size = sizeof(counter_id);
    key.mv_data = &counter_id;
    val.mv_size = sizeof(value);
    val.mv_data = &value;

    /* put the value into the database. */
    retval = mdb_put(txn, conn->global_db, &key, &val, 0);
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_DATABASE_PUT;
    }

    /* success. */
    return STATUS_SUCCESS;
}
