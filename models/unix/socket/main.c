#include <dangerfarm_contact/cbmc/model_assert.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../shadow/unix/unix_shadow.h"

int main(int argc, char* argv[])
{
    int desc;
    int retval;

    /* Create a socket instance. */
    desc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (desc < 0)
    {
        retval = 1;
        goto done;
    }

    /* Verify the socket is in range. */
    MODEL_ASSERT(desc >= 0 && desc <= SHADOW_FD_COUNT);

    /* close the socket. */
    close(desc);

    /* success. */
    retval = 0;
    goto done;

done:
    return retval;
}
