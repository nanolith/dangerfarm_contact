#pragma once

#ifdef __cplusplus
# define REQUIRE_SEMICOLON_HERE     static_assert(1, "dummy assertion")
#else
# define REQUIRE_SEMICOLON_HERE     _Static_assert(1, "dummy assertion")
#endif
