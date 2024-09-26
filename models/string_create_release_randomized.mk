ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	shadow/libcontact/string/prop_string_valid.c \
	../src/libcontact/string_create.c \
	../src/libcontact/string_release.c \
	string_create_release_randomized_main.c
