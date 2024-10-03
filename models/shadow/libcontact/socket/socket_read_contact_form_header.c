#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

#include "../../unix/unix_shadow.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

int nondet_status();
uint64_t nondet_uint64();

int DANGERFARM_CONTACT_SYM(socket_read_contact_form_header)(
    DANGERFARM_CONTACT_SYM(contact_form)* hdr, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_contact_form_header), hdr, s);

    int retval;

    /* does this read succeed? */
    if (0 == nondet_status())
    {
        hdr->name_size = nondet_uint64();
        hdr->email_size = nondet_uint64();
        hdr->subject_size = nondet_uint64();
        hdr->comment_size = nondet_uint64();
        retval = STATUS_SUCCESS;
        goto done;
    }
    else
    {
        retval = ERROR_SOCKET_READ;
        goto done;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(socket_read_contact_form_header), retval);

    return retval;
}
