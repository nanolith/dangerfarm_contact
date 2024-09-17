#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <unistd.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Write a \ref contact_form to the given descriptor.
 *
 * \param s             The descriptor to which the \ref contact_form is
 *                      written.
 * \param form          The \ref contact_form to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_write)(
    int s, const DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_write), s, form);

    int retval;
    size_t size = contact_form_compute_size(form);

    /* write the size bytes. */
    retval = socket_write_uint64(s, size);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* write the header. */
    retval = socket_write_contact_form_header(s, form);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* reduce the size by header bytes. */
    size -= sizeof(*form);

    /* write the data. */
    retval = socket_write_contact_form_data(s, form->data, size);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_write), retval);

    return retval;
}
