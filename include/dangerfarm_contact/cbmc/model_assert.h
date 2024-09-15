#pragma once

#include <assert.h>
#include <dangerfarm_contact/macro_tricks.h>

#ifdef CBMC
#define MODEL_ASSERT(x) __CPROVER_assert((x), #x); REQUIRE_SEMICOLON_HERE
#define MODEL_ASSUME(x) __CPROVER_assume((x)); REQUIRE_SEMICOLON_HERE
#define MODEL_EXEMPT(x)
#else
#define MODEL_ASSERT(x) REQUIRE_SEMICOLON_HERE
#define MODEL_ASSUME(x) REQUIRE_SEMICOLON_HERE
#define MODEL_EXEMPT(x) x
#endif
