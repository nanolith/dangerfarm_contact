#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

#include "contactdb_connection.h"

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
int contactdb_connection_form_append(
    contactdb_connection* conn, MDB_txn* txn, const contact_form* form)
{
    int retval;
    uint64_t count, contact_id;
    MDB_val key, val;

    /* get a unique contact id. */
    retval =
        contactdb_connection_counter_get_and_increment(
            conn, txn, COUNTER_ID_CONTACT_KEY, &contact_id);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* set up the payload for this transaction. */
    key.mv_size = sizeof(contact_id);
    key.mv_data = &contact_id;
    val.mv_size = contact_form_compute_size(form);
    val.mv_data = (void*)form;

    /* put this value into the database. */
    retval = mdb_put(txn, conn->contact_db, &key, &val, 0);
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_DATABASE_PUT;
    }

    /* increment the count. */
    retval =
        contactdb_connection_counter_get_and_increment(
            conn, txn, COUNTER_ID_CONTACT_COUNT, &count);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
