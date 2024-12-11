#include "../../src/contactform/contactform_internal.h"

int nondet_value();

int choose_req()
{
    int retval = nondet_value();

    MODEL_ASSUME(
        retval == CONTACTFORM_REQUEST_TYPE_OPTIONS
     || retval == CONTACTFORM_REQUEST_TYPE_POST);

    return retval;
}

int choose_invalid_req()
{
    int retval = nondet_value();

    MODEL_ASSUME(
        retval != CONTACTFORM_REQUEST_TYPE_OPTIONS
     && retval != CONTACTFORM_REQUEST_TYPE_POST);

    return retval;
}

int main(int argc, char* argv[])
{
    MODEL_ASSERT(prop_valid_request_type(choose_req()));
    MODEL_ASSERT(!prop_valid_request_type(choose_invalid_req()));

    return 0;
}
