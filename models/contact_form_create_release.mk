ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	../src/libcontact/contact_form_compute_size.c \
	../src/libcontact/contact_form_create.c \
	../src/libcontact/contact_form_release.c \
	contact_form_create_release_main.c
