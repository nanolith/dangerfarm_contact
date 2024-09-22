DF_EXPORT=dangerfarm_contact_6a32746c_5353_11ef_b2d0_18c04d8c76eb_V0_1_

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	shadow/unix/close.c \
	shadow/unix/prop_is_open_fd.c \
	shadow/unix/socket.c \
	shadow/unix/unix_shadow_init.c \
	shadow/libcontact/socket/socket_read_uint64.c \
	shadow/libcontact/socket/socket_read_contact_form_data.c \
	shadow/libcontact/socket/socket_read_contact_form_header.c \
	shadow/libcontact/string/string_filter_no_op.c \
	shadow/libcontact/string/string_release.c \
	shadow/libcontact/string/prop_string_valid.c \
	shadow/libcontact/data/contact_form_create_nondet.c \
	shadow/libcontact/data/contact_form_read.c \
	shadow/libcontact/data/contact_form_extract_name_nondet.c \
	shadow/libcontact/data/contact_form_extract_email_nondet.c \
	shadow/libcontact/data/contact_form_extract_subject_nondet.c \
	shadow/libcontact/data/contact_form_extract_comment_nondet.c \
	shadow/libcontact/data/prop_valid_contact_form.c \
	../src/libcontact/contact_form_compute_size.c \
	../src/libcontact/contact_form_release.c \
	../src/libcontact/contact_form_verify.c \
	contact_form_read_shadow_main.c
