#pragma once

#include <dangerfarm_contact/cbmc/function_contracts.h>
#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/function_decl.h>
#include <dangerfarm_contact/status_codes.h>
#include <lmdb.h>
#include <stdbool.h>
#include <stddef.h>

/* 20 MB is the default contact database size. */
#define CONTACTDB_SIZE      (20 * 1024 * 1024)

#define COUNTER_ID_CONTACT_COUNT        0x00000001
#define COUNTER_ID_CONTACT_KEY          0x00000002

#define COUNTER_VALUE_INVALID           UINT64_C(0xFFFFFFFFFFFFFFFF)

/* forward decl for contact form. */
typedef struct DANGERFARM_CONTACT_SYM(contact_form)
DANGERFARM_CONTACT_SYM(contact_form);

typedef struct contactdb_connection contactdb_connection;

struct contactdb_connection
{
    MDB_env* env;
    MDB_dbi global_db;
    MDB_dbi contact_db;
};

/* forward decls for external properties used in function contracts. */
bool prop_MDB_txn_valid(const MDB_txn* txn);

/**
 * \brief Return true if the given \ref contactdb_connection is valid.
 *
 * \param conn          The connection to verify.
 *
 * \returns true if this connection is valid, and false otherwise.
 */
bool prop_is_valid_contactdb_connection(const contactdb_connection* conn);

/**
 * \brief Return true if the given counter id is valid.
 *
 * \param counter_id    The counter id to verify.
 *
 * \returns true if this counter id is valid, and false otherwise.
 */
bool prop_is_valid_counter_id(uint64_t counter_id);

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
int FN_DECL_MUST_CHECK
contactdb_connection_create(contactdb_connection** conn, const char* path);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactdb_connection_create, contactdb_connection** conn, const char* path)
        /* conn variable must be accessible. */
        MODEL_CHECK_OBJECT_RW(conn, sizeof(*conn));
        /* path can't be NULL. */
        MODEL_ASSERT(NULL != path);
MODEL_CONTRACT_PRECONDITIONS_END(contactdb_connection_create)

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    contactdb_connection_create,
    int retval, contactdb_connection** conn)
        /* on success... */
        if (STATUS_SUCCESS == retval)
        {
            /* the connection is valid. */
            MODEL_ASSERT(prop_is_valid_contactdb_connection(*conn));
        }
        /* on failure... */
        else
        {
            /* the connection is set to NULL. */
            MODEL_ASSERT(NULL == *conn);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(contactdb_connection_create)

/**
 * \brief Release a contactdb connection.
 *
 * \param conn      The connection to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_connection_release(contactdb_connection* conn);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactdb_connection_release, contactdb_connection* conn)
        /* the connection is a valid pointer. */
        MODEL_ASSERT(NULL != conn);
MODEL_CONTRACT_PRECONDITIONS_END(contactdb_connection_release)

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    contactdb_connection_release, int retval)
MODEL_CONTRACT_POSTCONDITIONS_END(connection_release)

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
int FN_DECL_MUST_CHECK
contactdb_connection_counter_get_and_increment(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactdb_connection_counter_get_and_increment, contactdb_connection* conn,
    MDB_txn* txn, uint64_t counter_id, uint64_t* value)
        /* this is a valid connection. */
        MODEL_ASSERT(prop_is_valid_contactdb_connection(conn));
        /* this is a valid transaction. */
        MODEL_ASSERT(prop_MDB_txn_valid(txn));
        /* this is a valid counter id. */
        MODEL_ASSERT(prop_is_valid_counter_id(counter_id));
        /* the value is accessible. */
        MODEL_CHECK_OBJECT_RW(value, sizeof(*value));
MODEL_CONTRACT_PRECONDITIONS_END(contactdb_connection_counter_get_and_increment)

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    contactdb_connection_counter_get_and_increment, int retval, uint64_t* value)
        /* on success... */
        if (STATUS_SUCCESS == retval)
        {
            /* the counter value is NOT invalid. */
            MODEL_ASSERT(COUNTER_VALUE_INVALID != *value);
        }
        /* on failure... */
        else
        {
            /* the counter value is invalid. */
            MODEL_ASSERT(COUNTER_VALUE_INVALID == *value);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(
    contactdb_connection_counter_get_and_increment)

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
int FN_DECL_MUST_CHECK
contactdb_connection_counter_get_and_decrement(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactdb_connection_counter_get_and_decrement, contactdb_connection* conn,
    MDB_txn* txn, uint64_t counter_id, uint64_t* value)
        /* this is a valid connection. */
        MODEL_ASSERT(prop_is_valid_contactdb_connection(conn));
        /* this is a valid transaction. */
        MODEL_ASSERT(prop_MDB_txn_valid(txn));
        /* this is a valid counter id. */
        MODEL_ASSERT(prop_is_valid_counter_id(counter_id));
        /* the value is accessible. */
        MODEL_CHECK_OBJECT_RW(value, sizeof(*value));
MODEL_CONTRACT_PRECONDITIONS_END(contactdb_connection_counter_get_and_decrement)

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    contactdb_connection_counter_get_and_decrement, int retval, uint64_t* value)
        /* on success... */
        if (STATUS_SUCCESS == retval)
        {
            /* the counter value is NOT invalid. */
            MODEL_ASSERT(COUNTER_VALUE_INVALID != *value);
        }
        /* on failure... */
        else
        {
            /* the counter value is invalid. */
            MODEL_ASSERT(COUNTER_VALUE_INVALID == *value);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(
    contactdb_connection_counter_get_and_decrement)

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
int FN_DECL_MUST_CHECK
contactdb_connection_counter_get(
    contactdb_connection* conn, MDB_txn* txn, uint64_t counter_id,
    uint64_t* value);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactdb_connection_counter_get, contactdb_connection* conn,
    MDB_txn* txn, uint64_t counter_id, uint64_t* value)
        /* this is a valid connection. */
        MODEL_ASSERT(prop_is_valid_contactdb_connection(conn));
        /* this is a valid transaction. */
        MODEL_ASSERT(prop_MDB_txn_valid(txn));
        /* this is a valid counter id. */
        MODEL_ASSERT(prop_is_valid_counter_id(counter_id));
        /* the value is accessible. */
        MODEL_CHECK_OBJECT_RW(value, sizeof(*value));
MODEL_CONTRACT_PRECONDITIONS_END(contactdb_connection_counter_get)

/**
 * \brief Append a contact form record to the database.
 *
 * \note This function increments the KEY and COUNT counters.
 *
 * \param conn          The connection for this operation.
 * \param txn           The transaction for this operation.
 * \param form          The form to append.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_connection_form_append(
    contactdb_connection* conn, MDB_txn* txn,
    const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Get a form by id.
 *
 * \param conn          The connection for this operation.
 * \param txn           The transaction for this operation.
 * \param id            The id of the form to get.
 * \param form          Pointer to be set to the read-only form value.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_connection_form_get(
    contactdb_connection* conn, MDB_txn* txn, uint64_t id,
    const DANGERFARM_CONTACT_SYM(contact_form)** form);

/**
 * \brief Delete a form by id.
 *
 * \param conn          The connection for this operation.
 * \param txn           The transaction for this operation.
 * \param id            The id of the form to delete.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_connection_form_delete(
    contactdb_connection* conn, MDB_txn* txn, uint64_t id);

/**
 * \brief Get the first form associated with the contact database.
 *
 * \param cursor        Pointer to receive the cursor for this operation on
 *                      success.
 * \param conn          The connection for this operation.
 * \param txn           The transaction for this operation.
 * \param key           The key for this operation.
 * \param val           The value for this operation.
 * \param found         Pointer to the boolean value to be set to true if a
 *                      record was found.
 * \param p_key         If not NULL, set this pointer to the key value.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_connection_form_get_first(
    MDB_cursor** cursor, contactdb_connection* conn, MDB_txn* txn, MDB_val* key,
    MDB_val* val, bool* found, uint64_t* p_key);

/**
 * \brief Get the next form associated with the contact database.
 *
 * \param cursor        The cursor for this operation.
 * \param key           The key for this operation.
 * \param val           The value for this operation.
 * \param found         Pointer to the boolean value to be set to true if a
 *                      record was found.
 * \param p_key         If not NULL, set this pointer to the key value.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_connection_form_get_next(
    MDB_cursor* cursor, MDB_val* key, MDB_val* val, bool* found,
    uint64_t* p_key);
