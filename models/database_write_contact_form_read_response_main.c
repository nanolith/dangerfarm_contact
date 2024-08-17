#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "shadow/unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_protocol_database;

uint32_t nondet_u32();

int main(int argc, char* argv[])
{
    int retval;
    uint32_t status = nondet_u32();
    char NAME[9]; /* ignored by shadow contact_form_create. */
    size_t NAME_SIZE; /* ignored by shadow contact_form_create. */
    char EMAIL[9]; /* ignored by shadow contact_form_create. */
    size_t EMAIL_SIZE; /* ignored by shadow contact_form_create. */
    char SUBJECT[9]; /* ignored by shadow contact_form_create. */
    size_t SUBJECT_SIZE; /* ignored by shadow contact_form_create. */
    char COMMENT[9]; /* ignored by shadow contact_form_create. */
    size_t COMMENT_SIZE; /* ignored by shadow contact_form_create. */
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

    /* create a contact form instance. */
    retval = contact_form_create(&form, NAME, EMAIL, SUBJECT, COMMENT);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto close_sock;
    }

    /* "write" a database read contact form response to the socket. */
    retval = database_write_contact_form_read_response(sock, status, form);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto cleanup_form;
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
