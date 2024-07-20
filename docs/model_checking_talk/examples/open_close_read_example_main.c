#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int retval;
    int desc = -1;
    char buffer[5];

    /* open a file. */
    desc = open("/tmp/file.txt", O_CREAT | O_RDWR);
    if (desc < 0)
    {
        retval = 1;
        goto done;
    }

    /* read 5 bytes from the file. */
    ssize_t read_bytes = read(desc, buffer, 5);
    if (read_bytes < 0)
    {
        retval = 1;
        goto cleanup_desc;
    }

    /* success. */
    retval = 0;
    goto cleanup_desc;

cleanup_desc:
    /* close the file. */
    retval = close(desc);
    if (retval < 0)
    {
        retval = 1;
    }

done:
    return retval;
}
