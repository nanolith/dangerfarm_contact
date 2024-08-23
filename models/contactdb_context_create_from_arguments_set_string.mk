ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include -I $(HOME)/apps/lmdb/include \
	shadow/stdlib/strdup.c \
	../src/contactdb/contactdb_context_create_from_arguments_set_string.c \
	contactdb_context_create_from_arguments_set_string_main.c
