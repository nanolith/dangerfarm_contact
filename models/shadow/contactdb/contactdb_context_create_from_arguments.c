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
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_context_create_from_arguments, ctx, argc, argv);

    int retval, release_retval;
    contactdb_context* tmp = NULL;

    /* allocate memory for context. */
    tmp = (contactdb_context*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto fail;
    }

    memset(tmp, 0, sizeof(*tmp));
    tmp->sock = -1;
    tmp->listen_socket = true;

    /* create a dummy db path. */
    tmp->db_path = strdup("dbp");
    if (NULL == tmp->db_path)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* create a dummy socket path. */
    tmp->socket_path = strdup("sp");
    if (NULL == tmp->socket_path)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* create a dummy socket. */
    tmp->sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (tmp->sock < 0)
    {
        retval = ERROR_CONTACTDB_BIND_FAILURE;
        goto cleanup_tmp;
    }

    /* connect to the database. */
    retval = contactdb_connection_create(&tmp->conn, "fp");
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

fail:
    *ctx = NULL;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_context_create_from_arguments, retval, ctx);

    return retval;
}
