#include <dangerfarm_contact/cbmc/model_assert.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "unix_shadow.h"

int nondet_retval();

int accept(
    int s, struct sockaddr * restrict addr, socklen_t * restrict addrlen)
{
    MODEL_ASSERT(prop_is_open_fd(s));
    MODEL_CHECK_OBJECT_RW(addr, addrlen);

    return socket(AF_UNIX, SOCK_STREAM, 0);
}
