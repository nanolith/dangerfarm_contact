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
            return "Invalid continuation in multi-byte read.";
        case ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION:
            return "Overlong representation in multi-byte read.";
        case ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER:
            return "Unexpected character in multi-byte read.";
        case ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE:
            return "Codepoint out-of-range in multi-byte read.";
        case ERROR_CONTACT_FORM_WRITE:
            return "Contact form write.";
        case ERROR_CONTACT_FORM_READ:
            return "Contact form read.";
        case ERROR_CONTACT_FORM_INVALID:
            return "Contact form invalid.";
        case ERROR_SOCKET_WRITE:
            return "Socket write.";
        case ERROR_SOCKET_READ:
            return "Socket read.";
        case ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID:
            return "Unexpected request id.";
        case ERROR_DATABASE_PROTOCOL_INVALID_COUNT:
            return "Invalid count.";
        case ERROR_DATABASE_SYNC:
            return "Database sync.";
        case ERROR_DATABASE_ENV_CREATE:
            return "Database create environment.";
        case ERROR_DATABASE_SET_MAPSIZE:
            return "Database set map size.";
        case ERROR_DATABASE_SET_MAXDBS:
            return "Set max databases.";
        case ERROR_DATABASE_ENV_OPEN:
            return "Database open environment.";
        case ERROR_DATABASE_TXN_BEGIN:
            return "Database begin transaction.";
        case ERROR_DATABASE_DBI_OPEN:
            return "Database open handle.";
        case ERROR_DATABASE_TXN_COMMIT:
            return "Database commit transaction.";
        case ERROR_DATABASE_PUT:
            return "Database put.";
        case ERROR_DATABASE_GET:
            return "Database get.";
        case ERROR_DATABASE_DELETE:
            return "Database delete.";
        case ERROR_DATABASE_CURSOR_OPEN:
            return "Database open cursor.";
        case ERROR_DATABASE_CURSOR_GET:
            return "Database cursor get.";
        case ERROR_CONTACTDB_MISSING_PARAMETER:
            return "Missing parameter.";
        case ERROR_CONTACTDB_BAD_PARAMETER:
            return "Bad parameter.";
        default:
            return "Unknown error.";
    }
}
