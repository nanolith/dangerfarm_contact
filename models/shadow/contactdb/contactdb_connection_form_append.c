#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <string.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../lmdb/lmdb_internal.h"

int nondet_retval();

uint64_t nondet_value();

DANGERFARM_CONTACT_IMPORT_contact_form;

int contactdb_connection_form_append(
    contactdb_connection* conn, MDB_txn* txn, const contact_form* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_append, conn, txn, form);

    int retval = nondet_retval();
    switch (retval)
    {
        case STATUS_SUCCESS:
        case ERROR_DATABASE_GET:
        case ERROR_DATABASE_PUT:
        case ERROR_CONTACTDB_GET_INVALID_SIZE:
            goto done;

        default:
            retval = ERROR_DATABASE_GET;
            goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_form_append, retval);

    return retval;
}
