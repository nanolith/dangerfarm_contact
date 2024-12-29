#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

size_t nondet_size();

size_t choose_buffer_size(size_t max)
{
    size_t retval = nondet_size();

    if (retval > max)
        retval = max;

    return retval;
}

int main(int argc, char* argv[])
{
    int retval;
    uint8_t buffer[1024];
    size_t buffer_size = choose_buffer_size(1024);

    /* create a socket. */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        retval = 1;
        goto done;
    }

    /* write data to the socket. */
    retval = write(sock, buffer, buffer_size);
    if (buffer_size != retval)
    {
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
