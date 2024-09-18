#pragma once

#include <assert.h>
#include <dangerfarm_contact/macro_tricks.h>

#ifdef CBMC
#define MODEL_ASSERT(x) __CPROVER_assert((x), #x); REQUIRE_SEMICOLON_HERE
#define MODEL_CHECK_OBJECT_READ(x, size) \
    __CPROVER_assert(__CPROVER_r_ok((x), (size)), #x " read " #size); \
    REQUIRE_SEMICOLON_HERE
#define MODEL_CHECK_OBJECT_WRITE(x, size) \
    __CPROVER_assert(__CPROVER_w_ok((x), (size)), #x " write " #size); \
    REQUIRE_SEMICOLON_HERE
#define MODEL_CHECK_OBJECT_RW(x, size) \
    MODEL_CHECK_OBJECT_READ(x, size); \
    MODEL_CHECK_OBJECT_WRITE(x, size); \
    REQUIRE_SEMICOLON_HERE
#define MODEL_ASSUME(x) __CPROVER_assume((x)); REQUIRE_SEMICOLON_HERE
#define MODEL_EXEMPT(x)
#else
#define MODEL_ASSERT(x) REQUIRE_SEMICOLON_HERE
#define MODEL_CHECK_OBJECT_READ(x, size) REQUIRE_SEMICOLON_HERE
#define MODEL_CHECK_OBJECT_WRITE(x, size) REQUIRE_SEMICOLON_HERE
#define MODEL_CHECK_OBJECT_RW(x, size) REQUIRE_SEMICOLON_HERE
#define MODEL_ASSUME(x) REQUIRE_SEMICOLON_HERE
#define MODEL_EXEMPT(x) x
#endif
