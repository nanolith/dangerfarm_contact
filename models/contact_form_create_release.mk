DF_EXPORT=dangerfarm_contact_6a32746c_5353_11ef_b2d0_18c04d8c76eb_V0_1_

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset $(DF_EXPORT)string_create.0:7 \
	-I ../include \
	shadow/libcontact/data/prop_valid_contact_form.c \
	shadow/libcontact/string/string_create_nondet.c \
	shadow/libcontact/string/string_release.c \
	../src/libcontact/contact_form_compute_size.c \
	../src/libcontact/contact_form_create.c \
	../src/libcontact/contact_form_extract_name.c \
	../src/libcontact/contact_form_extract_email.c \
	../src/libcontact/contact_form_extract_subject.c \
	../src/libcontact/contact_form_extract_comment.c \
	../src/libcontact/contact_form_release.c \
	../src/libcontact/contact_form_verify.c \
	contact_form_create_release_main.c
