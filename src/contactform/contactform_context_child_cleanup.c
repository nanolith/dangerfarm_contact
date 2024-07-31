#include "contactform_internal.h"

/**
 * \brief Clean up context data before calling into the CGI parse child. This
 * function ensures, for instance, that when parsing untrusted network data, an
 * exploit has no access to the database socket.
 *
 * \param ctx           The cloned context for this operation.
 */
void contactform_context_child_cleanup(contactform_context* ctx)
{
    /* close the db socket if valid. */
    if (ctx->dbsock >= 0)
    {
        close(ctx->dbsock);
        ctx->dbsock = -1;
    }

    /* Invalidate the PID. */
    ctx->dbpid = 0;
}
