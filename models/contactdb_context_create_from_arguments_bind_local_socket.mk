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
	shadow/stdlib/strlcpy_nop.c \
	shadow/unix/socket.c \
	shadow/unix/unlink_nop.c \
	shadow/unix/bind_nop.c \
	shadow/unix/chmod.c \
	shadow/unix/listen.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/close.c \
	shadow/contactdb/contactdb_context_create_from_arguments_set_string.c \
	shadow/contactdb/contactdb_connection_release_nop.c \
	shadow/contactdb/contactdb_disable_signal_handler.c \
	../src/contactdb/contactdb_context_create_from_arguments_bind_local_socket.c \
	../src/contactdb/contactdb_context_release.c \
	contactdb_context_create_from_arguments_bind_local_socket_main.c
