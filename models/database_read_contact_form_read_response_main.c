#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

int main(int argc, char* argv[])
{
    int retval;
    uint32_t status;
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

    /* "read" a contact form read response from this socket. */
    retval = database_read_contact_form_read_response(&status, &form, sock);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto close_sock;
    }

    /* was the operation successful? */
    if (STATUS_SUCCESS != status)
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
