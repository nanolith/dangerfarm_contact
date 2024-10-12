#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "../src/contactdb/contactdb_connection.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

uint64_t nondet_counter_id();

int main(int argc, char* argv[])
{
    int retval, release_retval;
    contactdb_connection* conn;
    MDB_txn* txn;
    uint64_t counter = nondet_counter_id();
    uint64_t value;
    contact_form* form;

    /* create the contactdb connection. */
    retval = contactdb_connection_create(&conn, "path/to/db");
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* begin a transaction. */
    retval = mdb_txn_begin(conn->env, NULL, 0, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_connection;
    }

    /* create a contact form. */
    retval = contact_form_create(&form, "a", "b", "c", "d");
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto abort_txn;
    }

    /* append a form. */
    retval = contactdb_connection_form_append(conn, txn, form);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_form;
    }

    /* success. */
    retval = 0;
    goto cleanup_form;

cleanup_form:
    release_retval = contact_form_release(form);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = 1;
    }

abort_txn:
    mdb_txn_abort(txn);

cleanup_connection:
    release_retval = contactdb_connection_release(conn);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = 1;
    }

done:
    return retval;
}
