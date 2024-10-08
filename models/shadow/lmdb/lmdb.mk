LMDB_SHADOW_FILES=\
	shadow/lmdb/mdb_cursor_close.c \
	shadow/lmdb/mdb_cursor_get.c \
	shadow/lmdb/mdb_cursor_open.c \
	shadow/lmdb/mdb_dbi_close.c \
	shadow/lmdb/mdb_dbi_open.c \
	shadow/lmdb/mdb_env_close.c \
	shadow/lmdb/mdb_env_create.c \
	shadow/lmdb/mdb_env_open.c \
	shadow/lmdb/mdb_env_sync.c \
	shadow/lmdb/mdb_env_set_mapsize.c \
	shadow/lmdb/mdb_env_set_maxdbs.c \
	shadow/lmdb/mdb_del.c \
	shadow/lmdb/mdb_get.c \
	shadow/lmdb/mdb_put.c \
	shadow/lmdb/mdb_txn_abort.c \
	shadow/lmdb/mdb_txn_begin.c \
	shadow/lmdb/mdb_txn_commit.c \
	shadow/lmdb/prop_MDB_cursor_valid.c \
	shadow/lmdb/prop_MDB_dbi_valid.c \
	shadow/lmdb/prop_MDB_env_created.c \
	shadow/lmdb/prop_MDB_env_in_txn.c \
	shadow/lmdb/prop_MDB_env_opened.c \
	shadow/lmdb/prop_MDB_txn_valid.c

LMDB_SHADOW_UNWINDSET=\
    --unwindset prop_MDB_txn_valid:3
