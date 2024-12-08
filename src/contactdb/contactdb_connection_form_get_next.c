#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "contactdb_connection.h"

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
int contactdb_connection_form_get_next(
    MDB_cursor* cursor, MDB_val* key, MDB_val* val, bool* found,
    uint64_t* p_key)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_get_next, cursor, key, val, found, p_key);

    int retval;

    /* get the next contact. */
    retval = mdb_cursor_get(cursor, key, val, MDB_NEXT);
    if (MDB_NOTFOUND == retval)
    {
        retval = STATUS_SUCCESS;
        goto fail;
    }
    else if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_CURSOR_GET;
        goto fail;
    }

    /* verify the key size is correct. */
    if (key->mv_size != sizeof(uint64_t))
    {
        retval = ERROR_CONTACTDB_GET_INVALID_SIZE;
        goto fail;
    }

    /* copy the key. */
    if (NULL != p_key)
    {
        memcpy(p_key, key->mv_data, sizeof(uint64_t));

        if (COUNTER_VALUE_INVALID == *p_key)
        {
            retval = ERROR_CONTACTDB_BAD_COUNTER_VALUE;
            goto fail;
        }
    }

    /* success. */
    *found = true;
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *found = false;
    *p_key = COUNTER_VALUE_INVALID;
    key->mv_data = NULL; key->mv_size = 0;
    val->mv_data = NULL; val->mv_size = 0;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_form_get_next, retval, cursor, key, val, found,
        p_key);

    return retval;
}
