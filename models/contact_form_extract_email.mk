ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset contact_form_create.0:4,contact_form_create.1:4 \
	--unwindset contact_form_create.2:4,contact_form_create.3:4 \
	--unwindset string_create.0:7 \
	-I ../include \
	shadow/libcontact/data/prop_valid_contact_form.c \
	shadow/libcontact/data/contact_form_create_nondet.c \
	shadow/libcontact/string/string_create_nondet.c \
	shadow/libcontact/string/string_release.c \
	shadow/libcontact/string/prop_string_valid.c \
	../src/libcontact/contact_form_compute_size.c \
	../src/libcontact/contact_form_extract_email.c \
	../src/libcontact/contact_form_release.c \
	../src/libcontact/contact_form_verify.c \
	contact_form_extract_email_main.c
