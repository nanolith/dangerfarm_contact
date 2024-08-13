ALL:
	cbmc --bounds-check --pointer-check --memory-leak-check \
	--malloc-may-fail --malloc-fail-null \
	--div-by-zero-check --pointer-overflow-check --trace --stop-on-fail -DCBMC \
	--drop-unused-functions \
	--unwind 10 --unwinding-assertions \
	--unwindset string_create.0:7 \
	-I ../include -I $(HOME)/apps/lmdb/include \
	shadow/stdlib/strdup.c \
	strdup_shadow_main.c