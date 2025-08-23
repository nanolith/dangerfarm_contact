#include <dangerfarm_contact/cbmc/model_assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>

int nondet_signal();

bool prop_valid_signal(int signal)
{
    switch (signal)
    {
        case SIGHUP:
        case SIGTERM:
        case SIGINT:
            return true;
    }

    return false;
}

int choose_signal()
{
    int retval = nondet_signal();

    MODEL_ASSUME(prop_valid_signal(retval));

    return retval;
}

int main(int argc, char* argv[])
{
    int retval;
    struct sigaction sa;

    /* register a signal. */
    retval = sigaction(choose_signal(), &sa, NULL);
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
