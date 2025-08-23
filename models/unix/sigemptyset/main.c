#include <signal.h>

int main(int argc, char* argv[])
{
    int retval;
    struct sigaction sa;

    /* empty the signal set. */
    retval = sigemptyset(&sa.sa_mask);
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
