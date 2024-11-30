#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

DANGERFARM_CONTACT_IMPORT_protocol_database;

/* forward decls. */
static int id_vector_create(uint64_t** vec, uint64_t count);
static void id_vector_release(uint64_t* vec, uint64_t count);

/**
 * \brief Decode and dispatch a contactdb contact form get list request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int contactdb_dnd_contact_form_get_list(contactdb_context* ctx, int sock)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_dnd_contact_form_get_list, ctx, sock);

    int retval;
    uint64_t count = 0;
    uint64_t read_count = 0;
    uint64_t* id_list = NULL;
    MDB_txn* txn = NULL;
    MDB_cursor* cursor = NULL;
    MDB_val key, val;
    bool found = false;

    /* is this socket allowed to perform this operation? */
    if (
        !contactdb_has_capability(
            ctx, DATABASE_CAPABILITY_CONTACT_FORM_LIST_GET))
    {
        retval = ERROR_CONTACTDB_PERMISSION_DENIED;
        goto write_response;
    }

    /* create a read-only transaction. */
    retval = mdb_txn_begin(ctx->conn->env, NULL, MDB_RDONLY, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_TXN_BEGIN;
        goto write_response;
    }

    /* get the total count. */
    retval =
        contactdb_connection_counter_get(
            ctx->conn, txn, COUNTER_ID_CONTACT_COUNT, &count);
    if (STATUS_SUCCESS != retval)
    {
        goto rollback_txn;
    }

    /* create the id vector. */
    retval = id_vector_create(&id_list, count);
    if (STATUS_SUCCESS != retval)
    {
        goto rollback_txn;
    }

    /* handle the zero count case. */
    if (0 == count)
    {
        retval = STATUS_SUCCESS;
        goto rollback_txn;
    }

    /* get the first key and open the cursor. */
    retval =
        contactdb_connection_form_get_first(
            &cursor, ctx->conn, txn, &key, &val, &found, id_list);
    if (STATUS_SUCCESS != retval)
    {
        goto rollback_txn;
    }

    /* Check to see if we found a key. */
    if (!found)
    {
        count = 0;
        retval = STATUS_SUCCESS;
        goto close_cursor;
    }

    /* verify that we haven't exceeded our counts. */
    ++read_count;
    if (read_count > count)
    {
        retval = ERROR_CONTACTDB_COUNT_MISMATCH;
        goto close_cursor;
    }

    /* loop through the remaining entries. */
    while (read_count < count)
    {
        /* get the next form key. */
        retval =
            contactdb_connection_form_get_next(
                cursor, &key, &val, &found, id_list + read_count);
        if (STATUS_SUCCESS != retval)
        {
            goto close_cursor;
        }

        /* check to see if we found a key. */
        if (!found)
        {
            count = read_count;
            retval = STATUS_SUCCESS;
            goto close_cursor;
        }

        /* increment the read count. */
        ++read_count;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto close_cursor;

close_cursor:
    mdb_cursor_close(cursor);

rollback_txn:
    if (NULL != txn)
    {
        mdb_txn_abort(txn);
        txn = NULL;
    }

write_response:
    retval =
        database_write_contact_form_list_response(sock, retval, count, id_list);

    /* clean up the id list. */
    id_vector_release(id_list, count);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_dnd_contact_form_get_list, retval);

    return retval;
}

/**
 * \brief Create an id vector.
 *
 * \param vec           Pointer to the vector pointer to be set on success.
 * \param count         The number of entries in the vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
static int id_vector_create(uint64_t** vec, uint64_t count)
{
    /* allocate memory for the id list. */
    *vec = (uint64_t*)malloc(count * sizeof(uint64_t));
    if (NULL == *vec)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* clear this list. */
    memset(*vec, 0, count * sizeof(uint64_t));

    /* success. */
    return STATUS_SUCCESS;
}

/**
 * \brief Release an id vector.
 *
 * \param vec           Pointer to the vector pointer to be set on success.
 * \param count         The number of entries in the vector.
 */
static void id_vector_release(uint64_t* vec, uint64_t count)
{
    /* clean up the vector. */
    if (NULL != vec)
    {
        memset(vec, 0, count * sizeof(uint64_t));
        free(vec);
    }
}
