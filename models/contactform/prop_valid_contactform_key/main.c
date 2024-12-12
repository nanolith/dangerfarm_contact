#include "../../src/contactform/contactform_internal.h"

int nondet_value();

int choose_key()
{
    int retval = nondet_value();

    MODEL_ASSUME(
        retval == KEY_NAME || retval == KEY_EMAIL || retval == KEY_SUBJECT
     || retval == KEY_COMMENT);

    return retval;
}

int choose_invalid_key()
{
    int retval = nondet_value();

    MODEL_ASSUME(
        retval != KEY_NAME && retval != KEY_EMAIL && retval != KEY_SUBJECT
     && retval != KEY_COMMENT);

    return retval;
}

int main(int argc, char* argv[])
{
    MODEL_ASSERT(prop_valid_contactform_key(choose_key()));
    MODEL_ASSERT(!prop_valid_contactform_key(choose_invalid_key()));

    return 0;
}
