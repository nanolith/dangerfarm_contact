ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset read.0:9 \
	-I ../include \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/read_loop_constrained.c \
	shadow/unix/socket.c \
	shadow/unix/unix_shadow_init.c \
	shadow/libcontact/socket/socket_read_uint32.c \
	shadow/libcontact/socket/socket_read_uint64.c \
	../src/libcontact/database_read_contact_form_list_response.c \
	database_read_contact_form_list_response_main.c
