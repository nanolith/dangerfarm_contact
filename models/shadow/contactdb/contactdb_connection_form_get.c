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
    int retval;
    MODEL_ASSERT(prop_is_valid_contactdb_connection(conn));
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    MODEL_ASSERT(NULL != form);

    retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        retval = contact_form_create(form, "na", "em", "su", "co");
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }
        txn->temp_object = *form;

        MODEL_ASSERT(prop_valid_contact_form(*form));
        return STATUS_SUCCESS;
    }
    else
    {
        return ERROR_DATABASE_GET;
    }
}
