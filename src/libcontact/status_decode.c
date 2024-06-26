#include <dangerfarm_contact/status_codes.h>

/**
 * \brief Return a description string for a given status code.
 *
 * \param status            The status code to decode.
 *
 * \returns a string representing this status code, or an error string if it is
 * unknown.
 */
const char* status_decode(int status)
{
    switch (status)
    {
        case STATUS_SUCCESS:
            return "Success.";
        case ERROR_GENERAL_OUT_OF_MEMORY:
            return "Out of memory.";
        default:
            return "Unknown error.";
    }
}
