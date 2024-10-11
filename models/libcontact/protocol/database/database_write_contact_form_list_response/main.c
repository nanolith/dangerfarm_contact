#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_protocol_database;

uint32_t nondet_uint32();
uint64_t nondet_uint64();

uint64_t get_count()
{
    uint64_t count = nondet_uint64();

    if (count > 8)
    {
        count = 8;
    }

    return count;
}

void build_list(uint64_t* list, uint64_t count)
{
    for (uint64_t i = 0; i < count; ++i)
    {
        list[i] = nondet_uint64();
    }
}

int main(int argc, char* argv[])
{
    int retval;
    uint32_t status = nondet_uint32();
    uint64_t count = get_count();
    uint64_t list[8];

    build_list(list, count);

    /* initialize the unix shadow interface. */
    unix_shadow_init();

    /* create a socket. */
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0)
    {
        retval = 1;
        goto done;
    }

    /* "write" the list response to this socket. */
    retval =
        database_write_contact_form_list_response(sock, status, count, list);
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
