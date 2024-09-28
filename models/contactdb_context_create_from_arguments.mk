ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include -I $(HOME)/apps/lmdb/include \
	shadow/contactdb/contactdb_context_create_from_arguments_bind_local_socket.c \
	shadow/contactdb/contactdb_context_create_from_arguments_read_args.c \
	shadow/contactdb/contactdb_connection_create.c \
	shadow/contactdb/contactdb_connection_release_nop.c \
	shadow/contactdb/contactdb_disable_signal_handler.c \
	shadow/libcontact/string/prop_string_valid.c \
	shadow/libcontact/string/string_release.c \
	../src/contactdb/contactdb_context_create_from_arguments.c \
	../src/contactdb/contactdb_context_release.c \
	contactdb_context_create_from_arguments_main.c
