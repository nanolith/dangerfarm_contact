#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "contactform_internal.h"

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_protocol_database;

/* forward decls. */
_Noreturn static void contactform_database_helper_entry(int s);
static int connect_local_socket(int* dbsock);

/**
 * \brief Create a database helper connection.
 *
 * \param s             Pointer to the descriptor to be set to the socket to
 *                      set to the socket connection to the helper.
 * \param pid           Pointer to set to the process id of this helper.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_database_helper_create(int* s, pid_t* pid)
{
    int retval;
    int socks[2];

    /* create a socketpair. */
    retval = socketpair(AF_UNIX, SOCK_STREAM, 0, socks);
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_CONTACTFORM_SOCKETPAIR;
        goto done;
    }

    /* fork the process. */
    *pid = fork();

    /* parent? */
    if (0 != *pid)
    {
        close(socks[0]);
        *s = socks[1];
        retval = STATUS_SUCCESS;
        goto done;
    }

    /* child? */
    if (0 == *pid)
    {
        close(0); /* stdin. */
        close(1); /* stdout. */
        close(2); /* stderr. */
        close(socks[1]);

        /* we never return from here. */
        contactform_database_helper_entry(socks[0]);
    }

    /* If we make it here, fork failed, so report the error. */
    retval = ERROR_CONTACTFORM_FORK;
    goto cleanup_socks;

cleanup_socks:
    close(socks[0]);
    close(socks[1]);

done:
    return retval;
}

/**
 * \brief Entry point for the contactform database helper.
 *
 * \param s             The socket to use to communicate with the CGI script.
 *
 * \note This function does NOT return.
 */
_Noreturn static void contactform_database_helper_entry(int s)
{
    int retval, release_retval;
    int dbsock = -1;
    uint32_t req = 0, status = 0;
    contact_form* form = NULL;

    /* open a connection to the contact database. */
    retval = connect_local_socket(&dbsock);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* drop privileges. */
    retval = contactform_drop_privileges(DROP_PRIV_STEP_COMPLETE);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    /* read a request from the CGI socket. */
    retval = database_read_request_id(&req, s);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_dbsock;
    }

    /* does this request ID match? */
    if (DATABASE_REQUEST_ID_CONTACT_FORM_APPEND != req)
    {
        retval = ERROR_CONTACTDB_PERMISSION_DENIED;
        goto write_error_status;
    }

    /* read the payload from the request. */
    retval = database_read_contact_form_append_request_payload(&form, s);
    if (STATUS_SUCCESS != retval)
    {
        goto write_error_status;
    }

    /* forward the request to the database. */
    retval = database_write_contact_form_append_request(dbsock, form);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_form;
    }

    /* read the append response from the database. */
    retval = database_read_contact_form_append_response(&status, dbsock);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_form;
    }

    /* write the append response to the CGI socket. */
    retval = database_write_contact_form_append_response(s, status);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_form;
    }

    /* set retval to the status and clean up. */
    retval = (int)status;
    goto cleanup_form;

cleanup_form:
    release_retval = contact_form_release(form);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

write_error_status:
    retval = database_write_generic_response(s, req, retval);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
    }

cleanup_dbsock:
    close(dbsock);

done:
    close(s);

    exit(retval);
}

/**
 * \brief Connect to the local database socket.
 *
 * \param dbsock        Pointer to the variable to be set to the database socket
 *                      on success.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int connect_local_socket(int* dbsock)
{
    int retval;
    struct sockaddr_un addr;

    /* set the connect address. */
    addr.sun_family = AF_UNIX;
    strlcpy(addr.sun_path, CONTACTDB_SOCKET, sizeof(addr.sun_path));

    /* create a socket. */
    *dbsock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (*dbsock < 0)
    {
        retval = ERROR_CONTACTFORM_SOCKET;
        goto done;
    }

    /* connect to this socket. */
    retval = connect(*dbsock, (struct sockaddr*)&addr, sizeof(addr));
    if (retval < 0)
    {
        retval = ERROR_CONTACTFORM_CONNECT;
        goto cleanup_sock;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_sock:
    close(*dbsock);

done:
    memset(&addr, 0, sizeof(addr));

    return retval;
}
