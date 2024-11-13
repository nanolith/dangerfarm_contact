#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_protocol_database;

int main(int argc, char* argv[])
{
    int retval;
    uint32_t status = 0;
    uint64_t count = 0;
    uint64_t* list = NULL;

    /* initialize the unix shadow interface. */
    unix_shadow_init();

    /* create a socket. */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        retval = 1;
        goto done;
    }

    /* "read" the response from the socket. */
    retval =
        database_read_contact_form_list_response(&status, &count, &list, sock);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto close_sock;
    }

    if (STATUS_SUCCESS != status)
    {
        retval = 1;
        goto close_sock;
    }

    /* success. */
    retval = 0;
    goto cleanup_list;

cleanup_list:
    free(list);

close_sock:
    close(sock);

done:
    return retval;
}
