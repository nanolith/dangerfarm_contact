#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

uint64_t nondet_uint64();

int main(int argc, char* argv[])
{
    int retval;
    uint64_t val = nondet_uint64();

    /* initialize the unix shadow interface. */
    unix_shadow_init();

    /* create a socket. */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        retval = 1;
        goto done;
    }

    /* "write" to this socket. */
    retval = socket_write_uint64(sock, val);
    if (STATUS_SUCCESS != retval)
    {
        MODEL_ASSERT(ERROR_SOCKET_WRITE == retval);
        retval = 1;
        goto close_sock;
    }

    /* success. */
    retval = 0;
    goto close_sock;

close_sock:
    close(sock);

done:
    return retval;
}
