#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

int main(int argc, char* argv[])
{
    int retval;
    contact_form* form;

    /* initialize the unix shadow interface. */
    unix_shadow_init();

    /* create a socket. */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        retval = 1;
        goto done;
    }

    /* "read" database contact form append request payload from the socket. */
    retval = database_read_contact_form_append_request_payload(&form, sock);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto close_sock;
    }

    /* success. */
    retval = 0;
    goto cleanup_form;

cleanup_form:
    MODEL_ASSERT(STATUS_SUCCESS == contact_form_release(form));

close_sock:
    close(sock);

done:
    return retval;
}
