#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Release a \ref contact_form instance.
 *
 * \param form          The \ref contact_form instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contact_form_release(contact_form* form)
{
    size_t size = 0;

    /* this computation always succeeds. */
    size = contact_form_compute_size(form);

    /* clear memory. */
    memset(form, 0, size);

    /* free memory. */
    free(form);

    return STATUS_SUCCESS;
}
