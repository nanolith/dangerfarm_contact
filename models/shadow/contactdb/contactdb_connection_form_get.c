#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../lmdb/lmdb_internal.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

int nondet_retval();

int contactdb_connection_form_get(
    contactdb_connection* conn, MDB_txn* txn, uint64_t id,
    const contact_form** form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_get, conn, txn, id, form);

    int retval;

    retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        retval = contact_form_create(form, "na", "em", "su", "co");
        if (STATUS_SUCCESS != retval)
        {
            goto fail;
        }
        txn->temp_object = *form;

        MODEL_ASSERT(prop_valid_contact_form(*form));
        goto done;
    }
    else
    {
        retval = ERROR_DATABASE_GET;
        goto fail;
    }

fail:
    *form = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_form_get, retval, form);

    return retval;
}
