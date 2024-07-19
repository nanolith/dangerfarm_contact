#pragma once

#include <assert.h>

#ifdef CBMC
#define MODEL_ASSERT(x) __CPROVER_assert((x), #x)
#define MODEL_ASSUME(x) __CPROVER_assume((x))
#define MODEL_EXEMPT(x)
#else
#define MODEL_ASSERT(x)
#define MODEL_ASSUME(x)
#define MODEL_EXEMPT(x) x
#endif
