ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset string_create.0:7 \
	-I ../include -I $(HOME)/apps/lmdb/include \
	shadow/lmdb/mdb_dbi_close.c \
	shadow/lmdb/mdb_dbi_open.c \
	shadow/lmdb/mdb_env_close.c \
	shadow/lmdb/mdb_env_create.c \
	shadow/lmdb/mdb_env_open.c \
	shadow/lmdb/mdb_env_sync.c \
	shadow/lmdb/mdb_env_set_mapsize.c \
	shadow/lmdb/mdb_env_set_maxdbs.c \
	shadow/lmdb/mdb_txn_abort.c \
	shadow/lmdb/mdb_txn_begin.c \
	shadow/lmdb/mdb_txn_commit.c \
	shadow/lmdb/prop_MDB_env_created.c \
	shadow/lmdb/prop_MDB_env_in_txn.c \
	shadow/lmdb/prop_MDB_env_opened.c \
	shadow/lmdb/prop_MDB_txn_valid.c \
	../src/contactdb/contactdb_connection_create.c \
	../src/contactdb/contactdb_connection_release.c \
	contactdb_connection_create_release_main.c
