ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	shadow/libcontact/string/prop_string_valid.c \
	shadow/libcontact/string/string_create_nondet.c \
	shadow/libcontact/string/string_release.c \
	shadow/libcontact/string/string_filter_no_op.c \
	string_filter_no_op_main.c
