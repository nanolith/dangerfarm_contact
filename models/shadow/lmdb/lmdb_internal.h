#pragma once

#include <lmdb.h>
#include <stdbool.h>
#include <stdint.h>

struct MDB_env
{
    bool created;
    bool opened;
    bool in_txn;
    MDB_txn* txn;
    size_t dbi_count;
    size_t dbi_alloc_count;
};

struct MDB_txn
{
    MDB_env* env;
    MDB_txn* parent;
    unsigned int flags;
    size_t dbi_count;
    uint8_t* data_buffer;
    size_t data_buffer_size;
    void* temp_object;
};

struct MDB_cursor
{
    MDB_txn* txn;
    MDB_dbi dbi;
    uint8_t* key_buffer;
    size_t key_buffer_size;
    size_t count;
};

bool prop_MDB_env_created(const MDB_env* env);
bool prop_MDB_env_opened(const MDB_env* env);
bool prop_MDB_env_in_txn(const MDB_env* env);
bool prop_MDB_txn_valid(const MDB_txn* txn);
bool prop_MDB_dbi_valid(const MDB_env* env, MDB_dbi dbi);
bool prop_MDB_cursor_valid(const MDB_cursor* cursor);
