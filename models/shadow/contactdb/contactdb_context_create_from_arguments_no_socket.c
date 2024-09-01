#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../../../src/contactdb/contactdb_internal.h"

int contactdb_context_create_from_arguments(
    contactdb_context** ctx, int argc, char* argv[])
{
    int retval, release_retval;
    contactdb_context* tmp = NULL;

    /* allocate memory for context. */
    tmp = (contactdb_context*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    memset(tmp, 0, sizeof(*tmp));
    tmp->sock = -1;
    tmp->listen_socket = true;

    /* connect to the database. */
    retval = contactdb_connection_create(&tmp->conn, "fake path");
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    *ctx = tmp;
    goto done;

cleanup_tmp:
    release_retval = contactdb_context_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
