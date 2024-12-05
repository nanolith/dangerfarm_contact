#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "contactdb_connection.h"

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
int contactdb_connection_form_delete(
    contactdb_connection* conn, MDB_txn* txn, uint64_t id)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_delete, conn, txn, id);

    int retval;
    MDB_val key;
    uint64_t count;

    /* set up the key for the get request. */
    key.mv_size = sizeof(id);
    key.mv_data = &id;

    /* delete this entry from the database. */
    retval = mdb_del(txn, conn->contact_db, &key, NULL);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_DELETE;
        goto done;
    }

    /* decrement the count. */
    retval =
        contactdb_connection_counter_get_and_decrement(
            conn, txn, COUNTER_ID_CONTACT_COUNT, &count);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_form_delete, retval);

    return retval;
}
