#include "../../../src/contactform/contactform_internal.h"

/**
 * \brief Verify that the given drop privileges step is valid.
 *
 * \param step          The step to verify.
 *
 * \returns true if this step is valid and false otherwise.
 */
bool prop_valid_drop_privileges_step(int step)
{
    switch (step)
    {
        case DROP_PRIV_STEP_KCGI_PARSE:
        case DROP_PRIV_STEP_COMPLETE:
            return true;

        default:
            return false;
    }
}
