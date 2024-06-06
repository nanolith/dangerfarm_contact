ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset contact_form_create.0:4,contact_form_create.1:4 \
	--unwindset contact_form_create.2:4,contact_form_create.3:4 \
	-I ../include \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	shadow/unix/unix_shadow_init.c \
	shadow/libcontact/socket/socket_read_uint32.c \
	shadow/libcontact/string/string_filter_no_op.c \
	shadow/libcontact/string/string_release.c \
	shadow/libcontact/string/prop_string_valid.c \
	../src/libcontact/database_read_contact_form_append_response.c \
	database_read_contact_form_append_response_main.c
