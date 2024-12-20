#include "contactform_internal.h"

/**
 * \brief Decode the method type into a contact form request type.
 *
 * \param method        The KCGI HTTP request method to decode.
 *
 * \returns the request type to perform.
 */
int contactform_context_decode_request_type(int method)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactform_context_decode_request_type, method);

    int retval;

    switch (method)
    {
        case KMETHOD_OPTIONS:
            retval = CONTACTFORM_REQUEST_TYPE_OPTIONS;
            break;

        case KMETHOD_POST:
            retval = CONTACTFORM_REQUEST_TYPE_POST;
            break;

        default:
            retval = CONTACTFORM_REQUEST_TYPE_INVALID;
            break;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactform_context_decode_request_type, retval);

    return retval;
}
