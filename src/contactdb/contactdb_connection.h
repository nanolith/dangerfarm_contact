#pragma once

#include <lmdb.h>

/* 20 MB is the default contact database size. */
#define CONTACTDB_SIZE      (20 * 1024 * 1024)

#define COUNTER_ID_CONTACT_COUNT        0x00000001
#define COUNTER_ID_CONTACT_KEY          0x00000002

typedef struct contactdb_connection contactdb_connection;

struct contactdb_connection
{
    MDB_env* env;
    MDB_dbi global_db;
    MDB_dbi contact_db;
};

/**
 * \brief Given a database path, create a contactdb connection.
 *
 * \param conn      Pointer to the connection pointer to receive this connection
 *                  on success.
 * \param path      The path to the database to connect.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_connection_create(contactdb_connection** conn, const char* path);

/**
 * \brief Release a contactdb connection.
 *
 * \param conn      The connection to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_connection_release(contactdb_connection* conn);

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
    uint64_t* value);

/**
 * \brief Given a connection and a transaction, read and decrement the given
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
int contactdb_connection_counter_get_and_decrement(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value);

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
    uint64_t* value);
