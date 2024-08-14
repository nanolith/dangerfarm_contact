#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

int nondet_status();
uint64_t nondet_uint64();

int socket_read_contact_form_header(contact_form* hdr, int s)
{
    /* verify that this is an open fd. */
    MODEL_ASSERT(prop_is_open_fd(s));

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        hdr->name_size = nondet_uint64();
        hdr->email_size = nondet_uint64();
        hdr->subject_size = nondet_uint64();
        hdr->comment_size = nondet_uint64();
        return STATUS_SUCCESS;
    }
    else
    {
        return ERROR_SOCKET_READ;
    }
}
