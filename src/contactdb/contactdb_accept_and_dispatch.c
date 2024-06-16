#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#include "contactdb_internal.h"

/**
 * \brief Accept and dispatch a connection.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on a FATAL error.
 */
int contactdb_accept_and_dispatch(contactdb_context* ctx)
{
    int retval;

    /* accept a connection. */
    int sock = accept(ctx->sock, NULL, NULL);
    if (sock < 0)
    {
        if (EINTR == errno)
        {
            retval = STATUS_SUCCESS;
            goto done;
        }
        else
        {
            retval = ERROR_CONTACTDB_ACCEPT;
            goto done;
        }
    }

    /* decode and dispatch a single request. */
    retval = contactdb_decode_and_dispatch(ctx, sock);
    
    /* ignore the return code for this operation. */
    (void)retval;
    retval = STATUS_SUCCESS;

    /* clean up. */
    goto close_sock;

close_sock:
    close(sock);

done:
    return retval;
}
