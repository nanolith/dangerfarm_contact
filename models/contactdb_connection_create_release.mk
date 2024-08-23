include shadow/lmdb/lmdb.mk

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include -I $(HOME)/apps/lmdb/include $(LMDB_SHADOW_FILES) \
	../src/contactdb/contactdb_connection_create.c \
	../src/contactdb/contactdb_connection_release.c \
	contactdb_connection_create_release_main.c
