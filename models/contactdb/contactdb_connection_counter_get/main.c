#include <dangerfarm_contact/status_codes.h>
#include <stddef.h>

#include "../src/contactdb/contactdb_connection.h"

uint64_t nondet_counter_id();

uint64_t pick_counter_id()
{
    uint64_t retval = nondet_counter_id();

    /* this is a valid counter id. */
    MODEL_ASSUME(prop_is_valid_counter_id(retval));

    return retval;
}

int main(int argc, char* argv[])
{
    int retval, release_retval;
    contactdb_connection* conn;
    MDB_txn* txn;
    uint64_t counter = pick_counter_id();
    uint64_t value;

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

    /* get a counter. */
    retval = contactdb_connection_counter_get(conn, txn, counter, &value);
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
