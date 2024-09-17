#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <stdlib.h>
#include <string.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

/**
 * \brief Release a \ref contact_form instance.
 *
 * \param form          The \ref contact_form instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_release)(
    DANGERFARM_CONTACT_SYM(contact_form)* form)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_release), form);

    int retval;
    size_t size = 0;

    /* this computation always succeeds. */
    size = contact_form_compute_size(form);

    /* clear memory. */
    memset(form, 0, size);

    /* free memory. */
    free(form);

    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(contact_form_release), retval);

    return retval;
}
