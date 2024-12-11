#include "../../../src/contactform/contactform_internal.h"

/**
 * \brief Verify that the given request type is valid.
 *
 * \param req           The request type to verify.
 *
 * \returns true if this request type is valid and false otherwise.
 */
bool prop_valid_request_type(int req)
{
    switch (req)
    {
        case CONTACTFORM_REQUEST_TYPE_OPTIONS:
        case CONTACTFORM_REQUEST_TYPE_POST:
            return true;

        default:
            return false;
    }
}
