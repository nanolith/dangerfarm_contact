#include <dangerfarm_contact/cbmc/model_assert.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int desc, desc2;
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

    /* bind this socket. */
    retval = bind(desc, (struct sockaddr*)&addr, sizeof(addr));
    if (retval < 0)
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* listen on this socket. */
    retval = listen(desc, 5);
    if (retval < 0)
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* accept a connection from this listen socket. */
    desc2 = accept(desc, (struct sockaddr*)&addr, sizeof(addr));
    if (desc2 < 0)
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* success. */
    retval = 0;
    goto cleanup_desc2;

cleanup_desc2:
    /* close the socket. */
    close(desc2);

cleanup_desc:
    /* close the socket. */
    close(desc);

done:
    return retval;
}
