#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <kcgi.h>

#include "../../../src/contactform/contactform_internal.h"

/**
 * \brief Verify that the given request method is valid.
 *
 * \param method        The request method to verify.
 *
 * \returns true if this request method is valid and false otherwise.
 */
bool prop_valid_request_method(int method)
{
    switch (method)
    {
        case KMETHOD_OPTIONS:
        case KMETHOD_POST:
            return true;

        default:
            return false;
    }
}
