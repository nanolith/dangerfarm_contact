#include <dangerfarm_contact/cbmc/model_assert.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../../shadow/unix/unix_shadow.h"

int main(int argc, char* argv[])
{
    int desc;
    int retval;
    struct sockaddr_un addr;

    /* set the bind address. */
    addr.sun_family = AF_UNIX;
    strlcpy(addr.sun_path, "/tmp/test", sizeof(addr.sun_path));

    /* Create a socket instance. */
    desc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (desc < 0)
    {
        retval = 1;
        goto done;
    }

    /* Verify the socket is in range. */
    MODEL_ASSERT(desc >= 0 && desc <= SHADOW_FD_COUNT);

    /* bind this socket. */
    retval = bind(desc, (struct sockaddr*)&addr, sizeof(addr));
    if (retval < 0)
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* listen on this socket. */
    retval = listen(desc, 10);
    if (retval < 0)
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* success. */
    retval = 0;
    goto cleanup_desc;

cleanup_desc:
    /* close the socket. */
    close(desc);

done:
    return retval;
}
