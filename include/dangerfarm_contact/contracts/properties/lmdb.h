#pragma once

#include <lmdb.h>
#include <stdbool.h>

bool prop_MDB_env_created(const MDB_env* env);
bool prop_MDB_env_opened(const MDB_env* env);
bool prop_MDB_env_in_txn(const MDB_env* env);
bool prop_MDB_txn_valid(const MDB_txn* txn);
