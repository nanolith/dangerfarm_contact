SET(CBMC_OPTIONS
	"--bounds-check" "--pointer-check" "--memory-leak-check"
	"--malloc-may-fail" "--malloc-fail-null" "--div-by-zero-check"
    "--pointer-overflow-check" "--trace" "--stop-on-fail"
	"--drop-unused-functions" "--unwind" "10" "--unwinding-assertions")

SET(LMDB_SOURCES
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_cursor_close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_cursor_get.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_cursor_open.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_dbi_close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_dbi_open.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_env_close.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_env_create.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_env_open.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_env_sync.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_env_set_mapsize.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_env_set_maxdbs.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_del.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_get.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_put.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_txn_abort.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_txn_begin.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/mdb_txn_commit.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/prop_MDB_cursor_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/prop_MDB_dbi_valid.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/prop_MDB_env_created.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/prop_MDB_env_in_txn.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/prop_MDB_env_opened.c
    ${CMAKE_SOURCE_DIR}/models/shadow/lmdb/prop_MDB_txn_valid.c)

SET(LMDB_BUILD_OPTIONS "-I ${LMDB_INCLUDE_DIRS}")
SET(LMDB_UNWINDSET --unwindset prop_MDB_txn_valid:3)

ADD_SUBDIRECTORY(contactdb)
ADD_SUBDIRECTORY(cstring)
ADD_SUBDIRECTORY(libcontact)
ADD_SUBDIRECTORY(lmdb)
