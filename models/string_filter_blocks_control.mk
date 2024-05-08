ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	../src/libcontact/string_create.c \
	../src/libcontact/string_release.c \
	../src/libcontact/string_filter.c \
	string_filter_blocks_control_main.c
