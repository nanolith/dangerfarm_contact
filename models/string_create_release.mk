ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	-I ../include \
	../src/libcontact/string_create.c \
	../src/libcontact/string_release.c \
	string_create_release_main.c
