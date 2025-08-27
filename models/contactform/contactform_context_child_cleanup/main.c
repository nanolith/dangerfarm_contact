#include "../../src/contactform/contactform_internal.h"

int main(int argc, char* argv[])
{
    int retval;
    contactform_context* ctx;

    /* create the contactform context. */
    retval = contactform_context_create(&ctx);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* cache the dbpid. */
    pid_t dbpid = ctx->dbpid;

    /* clean up the child context prior to calling the CGI parse. */
    contactform_context_child_cleanup(ctx);

    /* child cleanup should have hidden the pid, so restore it. */
    MODEL_ASSERT( 0 == ctx->dbpid); ctx->dbpid = dbpid;

    /* release the context. */
    retval = contactform_context_release(ctx);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
