DF_EXPORT=dangerfarm_contact_6a32746c_5353_11ef_b2d0_18c04d8c76eb_V0_1_

include shadow/lmdb/lmdb.mk

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	$(LMDB_SHADOW_UNWINDSET) \
	-I ../include -I $(HOME)/apps/lmdb/include $(LMDB_SHADOW_FILES) \
	shadow/contactdb/contactdb_connection_counter_get.c \
	shadow/contactdb/contactdb_context_create_from_arguments.c \
	shadow/contactdb/contactdb_disable_signal_handler.c \
	shadow/contactdb/contactdb_has_capability.c \
	shadow/contactdb/prop_is_valid_contactdb_connection.c \
	shadow/libcontact/socket/socket_write_uint32.c \
	shadow/libcontact/socket/socket_write_uint64.c \
	shadow/libcontact/string/string_release.c \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	../src/contactdb/contactdb_connection_create.c \
	../src/contactdb/contactdb_connection_release.c \
	../src/contactdb/contactdb_context_release.c \
	../src/contactdb/contactdb_dnd_contact_form_get_count.c \
	../src/libcontact/database_write_contact_form_get_count_response.c \
	contactdb_dnd_contact_form_get_count_main.c
