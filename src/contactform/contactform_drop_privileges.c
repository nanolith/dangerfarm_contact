#include <dangerfarm_contact/status_codes.h>

#include "contactform_internal.h"

/**
 * \brief Perform a drop privileges step.
 *
 * \param step          The step to perform.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_drop_privileges(int step)
{
    (void)step;

    return STATUS_SUCCESS;
}
