#include <dangerfarm_contact/status_codes.h>

#include "../src/contactdb/contactdb_connection.h"

int main(int argc, char* argv[])
{
    int retval, release_retval;
    contactdb_connection* conn;

    /* create the contactdb connection. */
    retval = contactdb_connection_create(&conn, "path/to/db");
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* success. */
    retval = 0;
    goto cleanup_connection;

cleanup_connection:
    release_retval = contactdb_connection_release(conn);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = 1;
    }

done:
    return retval;
}
