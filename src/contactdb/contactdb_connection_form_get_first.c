#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "contactdb_connection.h"

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
int contactdb_connection_form_get_first(
    MDB_cursor** cursor, contactdb_connection* conn, MDB_txn* txn, MDB_val* key,
    MDB_val* val, bool* found, uint64_t* p_key)
{
    int retval;

    /* open a cursor over the contact database. */
    retval = mdb_cursor_open(txn, conn->contact_db, cursor);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_CURSOR_OPEN;
        goto done;
    }

    /* get the first contact. */
    retval = mdb_cursor_get(*cursor, key, val, MDB_FIRST);
    if (MDB_NOTFOUND == retval)
    {
        retval = STATUS_SUCCESS;
        *found = false;
        goto done;
    }
    else if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_CURSOR_GET;
        goto close_cursor;
    }

    /* verify the key size is correct. */
    if (key->mv_size != sizeof(uint64_t))
    {
        retval = ERROR_CONTACTDB_GET_INVALID_SIZE;
        goto close_cursor;
    }

    /* copy the key. */
    if (NULL != p_key)
    {
        memcpy(p_key, key->mv_data, sizeof(uint64_t));
    }

    /* success. */
    *found = true;
    retval = STATUS_SUCCESS;
    goto done;

close_cursor:
    mdb_cursor_close(*cursor);

done:
    return retval;
}
