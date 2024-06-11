#pragma once

#include <lmdb.h>

typedef struct contactdb_connection contactdb_connection;

struct contactdb_connection
{
    MDB_env* env;
    MDB_dbi global_db;
};
