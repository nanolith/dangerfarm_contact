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
            return "Encountered EOF when reading multi-byte sequence.";
        case ERROR_READ_MULTIBYTE_RAW_CONTINUATION:
            return "Encountered raw continuation byte in multi-byte read.";
        case ERROR_READ_MULTIBYTE_INVALID_CONTINUATION:
            return "Encountered invalid continuation byte in multi-byte read.";
        default:
            return "Unknown error.";
    }
}
