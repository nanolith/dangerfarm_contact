#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_util_socket;

size_t nondet_size();
char nondet_data();

size_t fill_data(char* buf, size_t size)
{
    /* pick a random fill size. */
    size_t fill_size = nondet_size();
    if (fill_size > size)
    {
        fill_size = size;
    }

    for (size_t i = 0; i < fill_size; ++i)
    {
        buf[i] = nondet_data();
    }

    return fill_size;
}

int main(int argc, char* argv[])
{
    int retval;
    char data[9];
    size_t size = sizeof(data);

    /* initialize the unix shadow interface. */
    unix_shadow_init();

    /* initialize the data to write. */
    size = fill_data(data, size);
    
    /* create a socket. */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        retval = 1;
        goto done;
    }

    /* "write" the data to this socket. */
    retval = socket_write_contact_form_data(sock, data, size);
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
