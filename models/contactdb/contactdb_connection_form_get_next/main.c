#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "../src/contactdb/contactdb_connection.h"

uint64_t nondet_counter_id();

int main(int argc, char* argv[])
{
    int retval, release_retval;
    contactdb_connection* conn;
    MDB_txn* txn;
    MDB_cursor* cursor;
    MDB_val key, val;
    bool found = false;
    uint64_t keyval;
    uint64_t kvalue = nondet_counter_id();

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

    /* open the cursor. */
    retval = mdb_cursor_open(txn, conn->contact_db, &cursor);
    if (STATUS_SUCCESS != retval)
    {
        goto abort_txn;
    }

    /* set up for the next key. */
    key.mv_data = &kvalue;
    key.mv_size = sizeof(kvalue);

    /* get the next form. */
    retval =
        contactdb_connection_form_get_next(cursor, &key, &val, &found, &keyval);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto close_cursor;
    }

    /* success. */
    retval = 0;
    goto close_cursor;

close_cursor:
    mdb_cursor_close(cursor);

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
