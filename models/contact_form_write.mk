DF_EXPORT=dangerfarm_contact_6a32746c_5353_11ef_b2d0_18c04d8c76eb_V0_1_

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset contact_form_create_nondet.0:4,contact_form_create_nondet.1:4 \
	--unwindset contact_form_create_nondet.2:4,contact_form_create_nondet.3:4 \
	-I ../include \
	shadow/libcontact/data/prop_valid_contact_form.c \
	shadow/libcontact/data/contact_form_create_nondet.c \
	shadow/libcontact/socket/socket_write_uint64.c \
	shadow/libcontact/string/prop_string_valid.c \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	shadow/unix/unix_shadow_init.c \
	../src/libcontact/contact_form_compute_size.c \
	../src/libcontact/contact_form_release.c \
	../src/libcontact/contact_form_verify.c \
	../src/libcontact/contact_form_write.c \
	../src/libcontact/socket_write_contact_form_data.c \
	../src/libcontact/socket_write_contact_form_header.c \
	contact_form_write_main.c
