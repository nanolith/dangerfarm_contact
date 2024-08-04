#pragma once

#include <lmdb.h>
#include <stdbool.h>

struct MDB_env
{
    bool opened;
    size_t dbi_count;
};

bool prop_MDB_env_created(const MDB_env* env);
bool prop_MDB_env_opened(const MDB_env* env);
