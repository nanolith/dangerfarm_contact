ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	shadow/libcontact/data/contact_form_create_nondet.c \
	shadow/libcontact/string/string_create_nondet.c \
	shadow/libcontact/string/string_release.c \
	../src/libcontact/contact_form_compute_size.c \
	../src/libcontact/contact_form_extract_email.c \
	../src/libcontact/contact_form_release.c \
	contact_form_extract_email_main.c
