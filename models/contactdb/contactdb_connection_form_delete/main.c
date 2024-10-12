#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "../src/contactdb/contactdb_connection.h"

uint64_t nondet_id();

int main(int argc, char* argv[])
{
    int retval, release_retval;
    contactdb_connection* conn;
    MDB_txn* txn;
    uint64_t id = nondet_id();

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

    /* delete a form. */
    retval = contactdb_connection_form_delete(conn, txn, id);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto abort_txn;
    }

    /* success. */
    retval = 0;
    goto abort_txn;

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
