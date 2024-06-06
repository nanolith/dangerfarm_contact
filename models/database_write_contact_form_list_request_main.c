#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

uint32_t nondet_uint32();

int main(int argc, char* argv[])
{
    int retval;

    /* initialize the unix shadow interface. */
    unix_shadow_init();

    /* create a socket. */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        retval = 1;
        goto done;
    }

    /* "write" a contact form list request to the socket. */
    retval = database_write_contact_form_list_request(sock);
    if (STATUS_SUCCESS != retval)
    {
        MODEL_ASSERT(ERROR_SOCKET_WRITE == retval);
        retval = 1;
        goto close_sock;
    }

    /* success. */
    retval = 0;
    goto close_sock;

close_sock:
    close(sock);

done:
    return retval;
}
