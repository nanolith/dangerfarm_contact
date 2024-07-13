#include <dangerfarm_contact/status_codes.h>

#include "contactdb_connection.h"

/**
 * \brief Get the next form associated with the contact database.
 *
 * \param cursor        The cursor for this operation.
 * \param key           The key for this operation.
 * \param val           The value for this operation.
 * \param found         Pointer to the boolean value to be set to true if a
 *                      record was found.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_connection_form_get_next(
    MDB_cursor* cursor, MDB_val* key, MDB_val* val, bool* found)
{
    int retval;

    /* get the next contact. */
    retval = mdb_cursor_get(cursor, key, val, MDB_NEXT);
    if (MDB_NOTFOUND == retval)
    {
        *found = false;
        return STATUS_SUCCESS;
    }
    else if (STATUS_SUCCESS != retval)
    {
        return ERROR_DATABASE_CURSOR_GET;
    }

    /* success. */
    *found = true;
    return STATUS_SUCCESS;
}
