#include "../../src/contactform/contactform_internal.h"

int nondet_value();

int choose_step()
{
    int retval = nondet_value();

    MODEL_ASSUME(
        retval == DROP_PRIV_STEP_KCGI_PARSE
     || retval == DROP_PRIV_STEP_COMPLETE);

    return retval;
}

int choose_invalid_step()
{
    int retval = nondet_value();

    MODEL_ASSUME(
        retval != DROP_PRIV_STEP_KCGI_PARSE
     && retval != DROP_PRIV_STEP_COMPLETE);

    return retval;
}

int main(int argc, char* argv[])
{
    MODEL_ASSERT(prop_valid_drop_privileges_step(choose_step()));
    MODEL_ASSERT(!prop_valid_drop_privileges_step(choose_invalid_step()));

    return 0;
}
