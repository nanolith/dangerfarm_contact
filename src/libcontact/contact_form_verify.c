#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

/**
 * \brief Given a serialized contact form and a size, verify that the contact
 * form is valid (i.e. that offsets are correct wrt size.)
 *
 * \param form          The contact form to verify.
 * \param size          The size of the contact form to verify.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_verify)(
    const DANGERFARM_CONTACT_SYM(contact_form)* form, size_t size)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_verify), form, size);

    int retval;

    /* the size must at least be large enough for the contact form. */
    if (size < sizeof(contact_form))
    {
        retval = ERROR_CONTACT_FORM_INVALID;
        goto done;
    }

    /* the computed size should match the given size. */
    size_t computed_size = contact_form_compute_size(form);
    if (computed_size != size)
    {
        retval = ERROR_CONTACT_FORM_INVALID;
        goto done;
    }

    /* the contact form size is valid. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_verify), retval);

    return retval;
}
