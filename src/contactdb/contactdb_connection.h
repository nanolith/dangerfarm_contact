#pragma once

#include <lmdb.h>

typedef struct contactdb_connection contactdb_connection;

struct contactdb_connection
{
    MDB_env* env;
    MDB_dbi global_db;
    MDB_dbi contact_db;
};

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
int contactdb_connection_create(contactdb_connection** conn, const char* path);
