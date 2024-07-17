#pragma once

enum contactform_drop_privileges_step
{
    DROP_PRIV_STEP_KCGI_PARSE = 1,
    DROP_PRIV_STEP_COMPLETE   = 2,
};

/**
 * \brief Perform a drop privileges step.
 *
 * \param step          The step to perform.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_drop_privileges(int step);
