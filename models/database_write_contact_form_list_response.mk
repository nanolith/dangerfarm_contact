ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset build_list.0:9 \
	-I ../include \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	shadow/unix/unix_shadow_init.c \
	shadow/unix/write.c \
	shadow/libcontact/socket/socket_write_uint32.c \
	shadow/libcontact/socket/socket_write_uint64.c \
	../src/libcontact/database_write_contact_form_list_response.c \
	database_write_contact_form_list_response_main.c
