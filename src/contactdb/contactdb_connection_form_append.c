#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

#include "contactdb_connection.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

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
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_append, conn, txn, form);

    int retval;
    uint64_t count, contact_id;
    MDB_val key, val;

    /* get a unique contact id. */
    retval =
        contactdb_connection_counter_get_and_increment(
            conn, txn, COUNTER_ID_CONTACT_KEY, &contact_id);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
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
        retval = ERROR_DATABASE_PUT;
        goto done;
    }

    /* increment the count. */
    retval =
        contactdb_connection_counter_get_and_increment(
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
        contactdb_connection_form_append, retval);

    return retval;
}
