DF_EXPORT=dangerfarm_contact_6a32746c_5353_11ef_b2d0_18c04d8c76eb_V0_1_

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	../src/libcontact/contact_form_compute_size.c \
	../src/libcontact/contact_form_release.c \
	../src/libcontact/contact_form_verify.c \
	shadow/libcontact/data/contact_form_create_nondet.c \
	shadow/libcontact/data/contact_form_extract_email_nondet.c \
	shadow/libcontact/data/prop_valid_contact_form.c \
	shadow/libcontact/string/string_release.c \
	shadow/libcontact/string/prop_string_valid.c \
	contact_form_extract_email_nondet_main.c
