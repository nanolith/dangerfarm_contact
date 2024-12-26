#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int retval;

    /* change the permissions of a file. */
    retval =
        chmod(
            "path/to/file",
            /* the model expects R/W user and R/W group only. */
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (retval < 0)
    {
        retval = 1;
        goto done;
    }

done:
    return retval;
}
