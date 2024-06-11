#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "contactdb_connection.h"

/**
 * \brief Release a contactdb connection.
 *
 * \param conn      The connection to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_connection_release(contactdb_connection* conn)
{
    int retval;

    /* synchronize the database. */
    retval = mdb_env_sync(conn->env, 1);
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_DATABASE_SYNC;
    }

    /* close all database connections. */
    mdb_dbi_close(conn->env, conn->global_db);
    mdb_dbi_close(conn->env, conn->contact_db);

    /* close the database environment. */
    mdb_env_close(conn->env);

    /* release the connection. */
    memset(conn, 0, sizeof(*conn));
    free(conn);

    return STATUS_SUCCESS;
}
