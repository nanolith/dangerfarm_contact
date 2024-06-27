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
        case ERROR_READ_MULTIBYTE_EOF:
            return "EOF reading multi-byte sequence.";
        case ERROR_READ_MULTIBYTE_RAW_CONTINUATION:
            return "Raw continuation during multi-byte read.";
        case ERROR_READ_MULTIBYTE_INVALID_CONTINUATION:
            return "Encountered invalid continuation byte in multi-byte read.";
        case ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION:
            return "Encountered overlong representation in multi-byte read.";
        case ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER:
            return "Encountered an unexpected multi-byte character.";
        case ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE:
            return "Encountered an out-of-range codepoint.";
        case ERROR_CONTACT_FORM_WRITE:
            return "Contact form write.";
        default:
            return "Unknown error.";
    }
}
