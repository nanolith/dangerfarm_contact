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
    switch (method)
    {
        case KMETHOD_OPTIONS:
            return CONTACTFORM_REQUEST_TYPE_OPTIONS;
        case KMETHOD_POST:
            return CONTACTFORM_REQUEST_TYPE_POST;
        default:
            return CONTACTFORM_REQUEST_TYPE_INVALID;
    }
}
