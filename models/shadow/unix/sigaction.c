#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>

struct sigaction global_sig = {
    .sa_handler = 0,
    .sa_sigaction = 0,
    .sa_flags = 0,
    .sa_mask = 0
};

static bool prop_expected_sig(int sig)
{
    switch (sig)
    {
        case SIGHUP:
        case SIGTERM:
        case SIGINT:
            return true;

        default:
            return false;
    }
}

int sigaction(
    int sig, const struct sigaction * restrict act,
    struct sigaction * restrict oact)
{
    MODEL_ASSERT(NULL != act);
    MODEL_ASSERT(NULL == oact);
    MODEL_ASSERT(prop_expected_sig(sig));

    int retval = nondet_retval();
    switch (retval)
    {
        case 0:
            break;

        default:
            errno = EINVAL;
            return -1;
    }

    memcpy(&global_sig, act, sizeof(*act));
    return 0;
}

bool prop_sighandler_set()
{
    return global_sig.sa_handler != NULL;
}

void call_sighandler(int sig)
{
    MODEL_ASSERT(prop_sighandler_set());
    (*global_sig.sa_handler)(sig);
}
