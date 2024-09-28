ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include -I $(HOME)/apps/lmdb/include \
	shadow/contactdb/contactdb_context_create_from_arguments_no_socket.c \
	shadow/contactdb/contactdb_connection_create.c \
	shadow/contactdb/contactdb_connection_release_nop.c \
	shadow/contactdb/contactdb_disable_signal_handler.c \
	shadow/contactdb/contactdb_install_signal_handler_nop.c \
	shadow/libcontact/string/prop_string_valid.c \
	shadow/libcontact/string/string_release.c \
	shadow/unix/close_nop.c \
	shadow/unix/fork.c \
	shadow/unix/setsid.c \
	../src/contactdb/contactdb_daemonize.c \
	../src/contactdb/contactdb_context_release.c \
	contactdb_daemonize_main.c
