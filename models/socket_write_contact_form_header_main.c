#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

uint64_t nondet_uint64();

int main(int argc, char* argv[])
{
    int retval;
    contact_form hdr;

    /* initialize the unix shadow interface. */
    unix_shadow_init();

    /* initialize the contact form header. */
    hdr.name_size = nondet_uint64();
    hdr.email_size = nondet_uint64();
    hdr.subject_size = nondet_uint64();
    hdr.comment_size = nondet_uint64();
    
    /* create a socket. */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        retval = 1;
        goto done;
    }

    /* "write" the header to this socket. */
    retval = socket_write_contact_form_header(sock, &hdr);
    if (STATUS_SUCCESS != retval)
    {
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
