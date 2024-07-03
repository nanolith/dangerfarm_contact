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
            return "success.";
        case ERROR_GENERAL_OUT_OF_MEMORY:
            return "out of memory.";
        case ERROR_READ_MULTIBYTE_EOF:
            return "eof reading multi-byte sequence.";
        case ERROR_READ_MULTIBYTE_RAW_CONTINUATION:
            return "raw continuation during multi-byte read.";
        case ERROR_READ_MULTIBYTE_INVALID_CONTINUATION:
            return "invalid continuation in multi-byte read.";
        case ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION:
            return "overlong representation in multi-byte read.";
        case ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER:
            return "unexpected character in multi-byte read.";
        case ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE:
            return "codepoint out-of-range in multi-byte read.";
        case ERROR_CONTACT_FORM_WRITE:
            return "contact form write.";
        case ERROR_CONTACT_FORM_READ:
            return "contact form read.";
        case ERROR_CONTACT_FORM_INVALID:
            return "contact form invalid.";
        case ERROR_SOCKET_WRITE:
            return "socket write.";
        case ERROR_SOCKET_READ:
            return "socket read.";
        case ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID:
            return "unexpected request id.";
        case ERROR_DATABASE_PROTOCOL_INVALID_COUNT:
            return "invalid count.";
        case ERROR_DATABASE_SYNC:
            return "database sync.";
        case ERROR_DATABASE_ENV_CREATE:
            return "database create environment.";
        case ERROR_DATABASE_SET_MAPSIZE:
            return "database set map size.";
        case ERROR_DATABASE_SET_MAXDBS:
            return "set max databases.";
        case ERROR_DATABASE_ENV_OPEN:
            return "database open environment.";
        case ERROR_DATABASE_TXN_BEGIN:
            return "database begin transaction.";
        case ERROR_DATABASE_DBI_OPEN:
            return "database open handle.";
        case ERROR_DATABASE_TXN_COMMIT:
            return "database commit transaction.";
        case ERROR_DATABASE_PUT:
            return "database put.";
        case ERROR_DATABASE_GET:
            return "database get.";
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
        case ERROR_CONTACTDB_SOCKET_PATH_TOO_LONG:
            return "Socket path too long.";
        case ERROR_CONTACTDB_SOCKET_FAILURE:
            return "socket failure.";
        case ERROR_CONTACTDB_BIND_FAILURE:
            return "bind failure.";
        case ERROR_CONTACTDB_LISTEN_FAILURE:
            return "listen failure.";
        case ERROR_CONTACTDB_CHMOD_FAILURE:
            return "chmod failure.";
        case ERROR_CONTACTDB_INVALID_ROLE:
            return "Invalid role.";
        case ERROR_CONTACTDB_ACCEPT:
            return "accept failure.";
        default:
            return "Unknown error.";
    }
}
