include shadow/lmdb/lmdb.mk

ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwind 10 \
	$(LMDB_SHADOW_UNWINDSET) \
	-I ../include -I $(HOME)/apps/lmdb/include $(LMDB_SHADOW_FILES) \
	shadow/contactdb/contactdb_connection_form_get_first.c \
	shadow/contactdb/prop_is_valid_contactdb_connection.c \
	shadow/libcontact/data/contact_form_create_nondet.c \
	shadow/libcontact/data/prop_valid_contact_form.c \
	shadow/libcontact/string/prop_string_valid.c \
	../src/contactdb/contactdb_connection_create.c \
	../src/contactdb/contactdb_connection_release.c \
	../src/libcontact/contact_form_compute_size.c \
	../src/libcontact/contact_form_verify.c \
	contactdb_connection_form_get_first_shadow_main.c
