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
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactdb_connection_release, conn);

    int release_retval;
    int retval = STATUS_SUCCESS;

    /* synchronize the database. */
    release_retval = mdb_env_sync(conn->env, 1);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = ERROR_DATABASE_SYNC;
    }

    /* close all database connections. */
    mdb_dbi_close(conn->env, conn->global_db);
    mdb_dbi_close(conn->env, conn->contact_db);

    /* close the database environment. */
    mdb_env_close(conn->env);

    /* release the connection. */
    memset(conn, 0, sizeof(*conn));
    free(conn);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(contactdb_connection_release, retval);

    return retval;
}
