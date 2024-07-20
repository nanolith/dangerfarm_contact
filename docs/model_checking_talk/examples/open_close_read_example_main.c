#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int retval;
    int desc = -1;

    /* open a file. */
    desc = open("/tmp/file.txt", O_CREAT | O_RDWR);
    if (desc < 0)
    {
        return 1;
    }

    /* close the file. */
    retval = close(desc);
    if (retval < 0)
    {
        return 1;
    }

    return 0;
}
