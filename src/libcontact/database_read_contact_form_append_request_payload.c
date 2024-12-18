#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

/**
 * \brief Read a contact form append request payload.
 *
 * \note On success, the contact form is owned by the caller and must be
 * released when no longer needed.
 *
 * \param form      Pointer to the contact form append request payload to be
 *                  updated with the created payload on success.
 * \param s         The socket from which this request payload is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_append_request_payload)(
    DANGERFARM_CONTACT_SYM(contact_form)** form, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_append_request_payload),
        form, s);

    int retval = contact_form_read(form, s);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_append_request_payload),
        retval, form);

    return retval;
}
