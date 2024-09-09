include shadow/lmdb/lmdb.mk

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	$(LMDB_SHADOW_UNWINDSET) \
	-I ../include -I $(HOME)/apps/lmdb/include $(LMDB_SHADOW_FILES) \
	shadow/contactdb/contactdb_context_create_from_arguments.c \
	shadow/contactdb/contactdb_connection_create.c \
	shadow/contactdb/contactdb_connection_release_nop.c \
	shadow/contactdb/contactdb_decode_and_dispatch.c \
	shadow/contactdb/contactdb_disable_signal_handler.c \
	shadow/contactdb/prop_is_valid_contactdb_context.c \
	shadow/contactdb/prop_is_valid_contactdb_connection_nop.c \
	shadow/libcontact/string/string_release.c \
	shadow/libcontact/random_status_code.c \
	shadow/unix/accept.c \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	../src/contactdb/contactdb_context_release.c \
	../src/contactdb/contactdb_accept_and_dispatch.c \
	contactdb_accept_and_dispatch_main.c
