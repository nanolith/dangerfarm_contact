#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "contactdb_connection.h"

/**
 * \brief Given a database path, create a contactdb connection.
 *
 * \param conn      Pointer to the connection pointer to receive this connection
 *                  on success.
 * \param path      The path to the database to connect.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_connection_create(contactdb_connection** conn, const char* path)
{
    int retval;
    contactdb_connection* tmp = NULL;
    MDB_txn* txn = NULL;

    /* allocate memory for the connection. */
    tmp = (contactdb_connection*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* clear memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* create the environment. */
    retval = mdb_env_create(&tmp->env);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_ENV_CREATE;
        goto cleanup_tmp;
    }

    /* set the database size. */
    retval = mdb_env_set_mapsize(tmp->env, CONTACTDB_SIZE);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_SET_MAPSIZE;
        goto close_env;
    }

    /* we need two database handles. */
    retval = mdb_env_set_maxdbs(tmp->env, 2);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_SET_MAXDBS;
        goto close_env;
    }

    /* set the flags for this database environment. */
    unsigned int flags = 0;
#ifdef __OpenBSD__
    flags |= MDB_WRITEMAP;
#endif

    /* open the environment. */
    retval = mdb_env_open(tmp->env, path, flags, 0600);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_ENV_OPEN;
        goto close_env;
    }

    /* create a transaction for opening the databases. */
    retval = mdb_txn_begin(tmp->env, NULL, 0, &txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_TXN_BEGIN;
        goto close_env;
    }

    /* open the global database. */
    retval = mdb_dbi_open(txn, "global.db", MDB_CREATE, &tmp->global_db);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_DBI_OPEN;
        goto rollback_txn;
    }

    /* open the contact database. */
    retval = mdb_dbi_open(txn, "contact.db", MDB_CREATE, &tmp->contact_db);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_DBI_OPEN;
        goto rollback_txn;
    }

    /* commit the open. */
    retval = mdb_txn_commit(txn);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_DATABASE_TXN_COMMIT;
        goto rollback_txn;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    *conn = tmp;
    goto done;

rollback_txn:
    mdb_txn_abort(txn);

close_env:
    mdb_env_close(tmp->env);

cleanup_tmp:
    memset(tmp, 0, sizeof(*tmp));
    free(tmp);

done:
    return retval;
}
