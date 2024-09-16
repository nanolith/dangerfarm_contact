DF_EXPORT=dangerfarm_contact_6a32746c_5353_11ef_b2d0_18c04d8c76eb_V0_1_

include shadow/lmdb/lmdb.mk

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
    --unwindset contact_form_create_nondet.0:4,contact_form_create_nondet.1:4 \
    --unwindset contact_form_create_nondet.2:4,contact_form_create_nondet.3:4 \
	$(LMDB_SHADOW_UNWINDSET) \
	-I ../include -I $(HOME)/apps/lmdb/include $(LMDB_SHADOW_FILES) \
	shadow/contactdb/contactdb_context_create_from_arguments.c \
	shadow/contactdb/contactdb_disable_signal_handler.c \
	shadow/contactdb/contactdb_dnd_contact_form_append.c \
	shadow/contactdb/contactdb_dnd_contact_form_delete.c \
	shadow/contactdb/contactdb_dnd_contact_form_get.c \
	shadow/contactdb/contactdb_dnd_contact_form_get_count.c \
	shadow/contactdb/contactdb_dnd_contact_form_get_list.c \
	shadow/contactdb/prop_is_valid_contactdb_connection.c \
	shadow/contactdb/prop_is_valid_contactdb_context.c \
	shadow/libcontact/random_status_code.c \
	shadow/libcontact/socket/socket_read_uint32.c \
	shadow/libcontact/socket/socket_write_uint32.c \
	shadow/libcontact/string/string_release.c \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	../src/contactdb/contactdb_connection_create.c \
	../src/contactdb/contactdb_connection_release.c \
	../src/contactdb/contactdb_context_release.c \
	../src/contactdb/contactdb_decode_and_dispatch.c \
	../src/libcontact/database_read_request_id.c \
	../src/libcontact/database_write_generic_response.c \
	contactdb_decode_and_dispatch_main.c