#include <unistd.h>

int main(int argc, char* argv[])
{
    int retval;

    retval = unlink("path/to/file");
    if (retval < 0)
    {
        retval = 1;
        goto done;
    }

    /* success. */
    retval = 0;
    goto done;

done:
    return retval;
}
