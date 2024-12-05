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
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_get, conn, txn, id, form);

    int retval;
    MDB_val key, val;

    /* set up the key for the get request. */
    key.mv_size = sizeof(id);
    key.mv_data = &id;

    /* get this value from the database. */
    retval = mdb_get(txn, conn->contact_db, &key, &val);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_GET;
        goto fail;
    }

    /* if the data size < contact form size, that's an error. */
    if (val.mv_size < sizeof(contact_form))
    {
        retval = ERROR_DATABASE_GET;
        goto fail;
    }

    /* copy the returned data. */
    *form = (const contact_form*)val.mv_data;

    /* if the computed size < the data size, that's an error. */
    size_t computed_size = contact_form_compute_size(*form);
    if (val.mv_size < computed_size)
    {
        retval = ERROR_DATABASE_GET;
        goto fail;
    }

    /* we should be able to verify this contact form. */
    if (STATUS_SUCCESS != contact_form_verify(*form, computed_size))
    {
        retval = ERROR_DATABASE_GET;
        goto fail;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

fail:
    *form = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_form_get, retval, form);

    return retval;
}
