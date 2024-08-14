#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

#include "contactdb_connection.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

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
int contactdb_connection_form_get(
    contactdb_connection* conn, MDB_txn* txn, uint64_t id,
    const contact_form** form)
{
    int retval;
    MDB_val key, val;

    /* set up the key for the get request. */
    key.mv_size = sizeof(id);
    key.mv_data = &id;

    /* get this value from the database. */
    retval = mdb_get(txn, conn->contact_db, &key, &val);
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_DATABASE_GET;
    }

    /* copy the returned data. */
    *form = (const contact_form*)val.mv_data;

    /* success. */
    return STATUS_SUCCESS;
}
