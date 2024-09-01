ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include -I $(HOME)/apps/lmdb/include \
	shadow/contactdb/contactdb_connection_create.c \
	shadow/contactdb/contactdb_connection_release_nop.c \
	shadow/contactdb/contactdb_context_create_from_arguments.c \
	shadow/contactdb/contactdb_disable_signal_handler.c \
	shadow/libcontact/string/string_release.c \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	../src/contactdb/contactdb_context_release.c \
	../src/contactdb/contactdb_has_capability.c \
	contactdb_has_capability_main.c
