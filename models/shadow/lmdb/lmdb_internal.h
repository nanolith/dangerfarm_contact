#pragma once

#include <lmdb.h>
#include <stdbool.h>

struct MDB_env
{
    bool opened;
    size_t dbi_count;
};
