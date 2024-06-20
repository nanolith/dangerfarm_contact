#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "contactdb_connection.h"
#include "contactdb_internal.h"

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
    int retval;
    uint64_t count = 0;
    uint64_t read_count = 0;
    uint64_t* id_list = NULL;
    MDB_txn* txn = NULL;
    MDB_cursor* cursor = NULL;
    MDB_val key, val;

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

    /* allocate memory for the id list. */
    id_list = (uint64_t*)malloc(count * sizeof(uint64_t));
    if (NULL == id_list)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto rollback_txn;
    }

    /* clear this list. */
    memset(id_list, 0, count * sizeof(id_list));

    /* open a cursor on the contact database. */
    retval = mdb_cursor_open(txn, ctx->conn->contact_db, &cursor);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_CURSOR_OPEN;
        goto rollback_txn;
    }

    /* get the first contact. */
    retval = mdb_cursor_get(cursor, &key, &val, MDB_FIRST);
    if (MDB_NOTFOUND == retval)
    {
        count = 0;
        retval = STATUS_SUCCESS;
        goto close_cursor;
    }
    else if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_CURSOR_GET;
        goto close_cursor;
    }

    /* verify that we haven't exceeded our counts. */
    ++read_count;
    if (read_count > count)
    {
        retval = ERROR_CONTACTDB_COUNT_MISMATCH;
        goto close_cursor;
    }

    /* verify the key size is correct. */
    if (key.mv_size != sizeof(uint64_t))
    {
        retval = ERROR_CONTACTDB_GET_INVALID_SIZE;
        goto close_cursor;
    }

    /* save the first entry. */
    memcpy(id_list, key.mv_data, sizeof(uint64_t));

    /* loop through the remaining entries. */
    while (read_count < count)
    {
        /* get the next contact. */
        retval = mdb_cursor_get(cursor, &key, &val, MDB_NEXT);
        if (MDB_NOTFOUND == retval)
        {
            count = read_count;
            retval = STATUS_SUCCESS;
            goto close_cursor;
        }
        else if (STATUS_SUCCESS != retval)
        {
            retval = ERROR_DATABASE_CURSOR_GET;
            goto close_cursor;
        }

        /* verify that we haven't exceeded our counts. */
        if (read_count + 1 > count)
        {
            retval = ERROR_CONTACTDB_COUNT_MISMATCH;
            goto close_cursor;
        }

        /* verify the key size is correct. */
        if (key.mv_size != sizeof(uint64_t))
        {
            retval = ERROR_CONTACTDB_GET_INVALID_SIZE;
            goto close_cursor;
        }

        /* save this entry. */
        memcpy(id_list + read_count, key.mv_data, sizeof(uint64_t));

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
    if (NULL != id_list)
    {
        memset(id_list, 0, count * sizeof(uint64_t));
        free(id_list);
        id_list = NULL;
    }

    return retval;
}
