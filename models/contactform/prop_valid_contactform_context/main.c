#include "../../src/contactform/contactform_internal.h"

int nondet_socket();
pid_t nondet_pid();

int choose_valid_socket()
{
    int retval = nondet_socket();
    MODEL_ASSUME(retval >= 0);

    return retval;
}

pid_t choose_valid_pid()
{
    pid_t retval = nondet_pid();
    MODEL_ASSUME(retval >= 0);

    return retval;
}

int main(int argc, char* argv[])
{
    contactform_context ctx;

    memset(&ctx, 0, sizeof(ctx));
    ctx.dbsock = choose_valid_socket();
    ctx.dbpid = choose_valid_pid();

    MODEL_ASSERT(prop_valid_contactform_context(&ctx));

    return 0;
}
