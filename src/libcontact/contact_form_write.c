#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <unistd.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

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
int contact_form_write(int s, const contact_form* form)
{
    MODEL_ASSERT(prop_valid_contact_form(form));

    int retval;
    size_t size = contact_form_compute_size(form);

    /* write the size bytes. */
    retval = socket_write_uint64(s, size);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the header. */
    retval = socket_write_contact_form_header(s, form);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* reduce the size by header bytes. */
    size -= sizeof(*form);

    /* write the data. */
    retval = socket_write_contact_form_data(s, form->data, size);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
