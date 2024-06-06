ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset contact_form_create.0:4,contact_form_create.1:4 \
	--unwindset contact_form_create.2:4,contact_form_create.3:4 \
	-I ../include \
	shadow/libcontact/socket/socket_write_uint32.c \
	shadow/libcontact/socket/socket_write_uint64.c \
	shadow/libcontact/string/prop_string_valid.c \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	shadow/unix/unix_shadow_init.c \
	../src/libcontact/database_write_contact_form_get_count_response.c \
	database_write_contact_form_get_count_response_main.c
