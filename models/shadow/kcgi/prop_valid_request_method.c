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
        case KMETHOD_ACL:
        case KMETHOD_CONNECT:
        case KMETHOD_COPY:
        case KMETHOD_DELETE:
        case KMETHOD_GET:
        case KMETHOD_HEAD:
        case KMETHOD_LOCK:
        case KMETHOD_MKCALENDAR:
        case KMETHOD_MKCOL:
        case KMETHOD_MOVE:
        case KMETHOD_OPTIONS:
        case KMETHOD_POST:
        case KMETHOD_PROPFIND:
        case KMETHOD_PROPPATCH:
        case KMETHOD_PUT:
        case KMETHOD_REPORT:
        case KMETHOD_TRACE:
            return true;

        default:
            return false;
    }
}
