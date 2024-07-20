ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	shadow/close.c \
	shadow/open.c \
	shadow/prop_is_valid_unix_desc.c \
	shadow/read.c \
	open_close_read_example_main.c
