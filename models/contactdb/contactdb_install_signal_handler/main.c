#include <dangerfarm_contact/status_codes.h>

#include "../src/contactdb/contactdb_internal.h"
#include "shadow/unix/unix_shadow.h"
#include <signal.h>

int nondet_signal();
int possible_signals()
{
    int sig = nondet_signal();

    switch (sig)
    {
        case SIGHUP:
        case SIGINT:
        case SIGQUIT:
        case SIGILL:
        case SIGTRAP:
        case SIGABRT:
        case SIGEMT:
        case SIGFPE:
        case SIGKILL:
        case SIGBUS:
        case SIGSEGV:
        case SIGSYS:
        case SIGPIPE:
        case SIGALRM:
        case SIGTERM:
        case SIGURG:
        case SIGSTOP:
        case SIGTSTP:
        case SIGCONT:
        case SIGCHLD:
        case SIGTTIN:
        case SIGTTOU:
        case SIGIO:
        case SIGXCPU:
        case SIGXFSZ:
        case SIGVTALRM:
        case SIGPROF:
        case SIGWINCH:
        case SIGINFO:
        case SIGUSR1:
        case SIGUSR2:
        case SIGTHR:
        #ifndef __OpenBSD__
        case SIGLIBRT:
        #endif
            return sig;

        default:
            return SIGHUP;
    }
}

int main(int argc, char* argv[])
{
    int retval;
    contactdb_context* ctx;

    /* create a context from arguments. */
    retval = contactdb_context_create_from_arguments(&ctx, argc, argv);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* install the signal handler. */
    retval = contactdb_install_signal_handler(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_ctx;
    }

    /* call the signal handler. */
    call_sighandler(possible_signals());

    /* clean up the context. */
    retval = contactdb_context_release(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* call the signal handler. */
    call_sighandler(possible_signals());

    retval = 0;
    goto done;
    
cleanup_ctx:
    retval = contactdb_context_release(ctx);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
    }

done:
    return retval;
}
