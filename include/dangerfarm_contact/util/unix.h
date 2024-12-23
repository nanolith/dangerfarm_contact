#pragma once

#include <unistd.h>

#ifdef   __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* When model checking, we want to be able to override close_fd. */
#ifdef CBMC
int close_fd(int fd);
/* in production, this is just inline for close(). */
#else
static inline int close_fd(int fd)
{
    return close(fd);
}
#endif

#ifdef   __cplusplus
}
#endif /*__cplusplus*/
