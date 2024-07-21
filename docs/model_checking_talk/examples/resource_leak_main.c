#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int retval;
    int desc = -1;
    char buffer[5];
    uint64_t counter;

    /* open the counter file. */
    desc = open("/var/data/counter.txt", O_RDWR);
    if (desc < 0)
    {
        retval = 1;
        goto done;
    }

    /* read the counter. */
    ssize_t read_bytes = read(desc, &counter, sizeof(counter));
    if (read_bytes < 0 || read_bytes != sizeof(counter))
    {
        retval = 1;
        goto done;
    }

    /* increment the counter. */
    ++counter;

    /* write the counter. */
    ssize_t wrote_bytes = write(desc, &counter, sizeof(counter));
    if (wrote_bytes < 0 || wrote_bytes != sizeof(counter))
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
