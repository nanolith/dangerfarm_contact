#include <dangerfarm_contact/status_codes.h>

#include "contactform_internal.h"

/* forward decls. */
static int drop_privileges_for_parse(void);
static int drop_all_privileges(void);

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
    switch (step)
    {
        case DROP_PRIV_STEP_KCGI_PARSE:
            return drop_privileges_for_parse();

        case DROP_PRIV_STEP_COMPLETE:
            return drop_all_privileges();

        default:
            return ERROR_CONTACTFORM_INVALID_DROP_PRIVILEGES_STEP;
    }
}

/**
 * \brief Drop privileges prior to the kcgi parse step.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int drop_privileges_for_parse(void)
{
    return STATUS_SUCCESS;
}

/**
 * \brief Drop all privileges prior to running the main CGI app.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int drop_all_privileges(void)
{
    return STATUS_SUCCESS;
}
