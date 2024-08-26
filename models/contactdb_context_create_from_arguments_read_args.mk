ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include -I $(HOME)/apps/lmdb/include \
	shadow/libcontact/string/string_release.c \
	shadow/stdlib/strdup.c \
	shadow/stdlib/strcmp.c \
	shadow/contactdb/contactdb_context_create_from_arguments_set_string.c \
	shadow/contactdb/contactdb_connection_release_nop.c \
	shadow/contactdb/getopt.c \
	../src/contactdb/contactdb_context_create_from_arguments_read_args.c \
	../src/contactdb/contactdb_context_release.c \
	contactdb_context_create_from_arguments_read_args_main.c