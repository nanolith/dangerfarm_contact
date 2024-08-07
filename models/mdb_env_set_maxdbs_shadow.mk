ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset string_create.0:7 \
	-I ../include -I $(HOME)/apps/lmdb/include \
	shadow/lmdb/mdb_env_create.c \
	shadow/lmdb/mdb_env_close.c \
	shadow/lmdb/mdb_env_set_maxdbs.c \
	shadow/lmdb/prop_MDB_env_created.c \
	shadow/lmdb/prop_MDB_env_in_txn.c \
	shadow/lmdb/prop_MDB_env_opened.c \
	mdb_env_set_maxdbs_shadow_main.c
