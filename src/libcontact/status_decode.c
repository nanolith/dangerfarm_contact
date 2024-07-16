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
            return "success";
        case ERROR_GENERAL_OUT_OF_MEMORY:
            return "out of memory";
        case ERROR_READ_MULTIBYTE_EOF:
            return "eof reading multi-byte sequence";
        case ERROR_READ_MULTIBYTE_RAW_CONTINUATION:
            return "raw continuation during multi-byte read";
        case ERROR_READ_MULTIBYTE_INVALID_CONTINUATION:
            return "invalid continuation in multi-byte read";
        case ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION:
            return "overlong representation in multi-byte read";
        case ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER:
            return "unexpected character in multi-byte read";
        case ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE:
            return "codepoint out-of-range in multi-byte read";
        case ERROR_CONTACT_FORM_WRITE:
            return "contact form write";
        case ERROR_CONTACT_FORM_READ:
            return "contact form read";
        case ERROR_CONTACT_FORM_INVALID:
            return "contact form invalid";
        case ERROR_SOCKET_WRITE:
            return "socket write";
        case ERROR_SOCKET_READ:
            return "socket read";
        case ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID:
            return "unexpected request id";
        case ERROR_DATABASE_PROTOCOL_INVALID_COUNT:
            return "invalid count";
        case ERROR_DATABASE_SYNC:
            return "database sync";
        case ERROR_DATABASE_ENV_CREATE:
            return "database create environment";
        case ERROR_DATABASE_SET_MAPSIZE:
            return "database set map size";
        case ERROR_DATABASE_SET_MAXDBS:
            return "set max databases";
        case ERROR_DATABASE_ENV_OPEN:
            return "database open environment";
        case ERROR_DATABASE_TXN_BEGIN:
            return "database begin transaction";
        case ERROR_DATABASE_DBI_OPEN:
            return "database open handle";
        case ERROR_DATABASE_TXN_COMMIT:
            return "database commit transaction";
        case ERROR_DATABASE_PUT:
            return "database put";
        case ERROR_DATABASE_GET:
            return "database get";
        case ERROR_DATABASE_DELETE:
            return "database delete";
        case ERROR_DATABASE_CURSOR_OPEN:
            return "database open cursor";
        case ERROR_DATABASE_CURSOR_GET:
            return "database cursor get";
        case ERROR_CONTACTDB_MISSING_PARAMETER:
            return "missing parameter";
        case ERROR_CONTACTDB_BAD_PARAMETER:
        case ERROR_CTOOL_BAD_PARAMETER:
            return "bad parameter";
        case ERROR_CONTACTDB_SOCKET_PATH_TOO_LONG:
        case ERROR_CTOOL_SOCKET_PATH_TOO_LONG:
            return "socket path too long";
        case ERROR_CONTACTDB_SOCKET_FAILURE:
        case ERROR_CTOOL_SOCKET_FAILURE:
            return "socket failure";
        case ERROR_CONTACTDB_BIND_FAILURE:
            return "bind failure";
        case ERROR_CONTACTDB_LISTEN_FAILURE:
            return "listen failure";
        case ERROR_CONTACTDB_CHMOD_FAILURE:
            return "chmod failure";
        case ERROR_CONTACTDB_INVALID_ROLE:
            return "invalid role";
        case ERROR_CONTACTDB_ACCEPT:
            return "accept failure";
        case ERROR_CONTACTDB_PERMISSION_DENIED:
            return "permission denied";
        case ERROR_CONTACTDB_SIGACTION_FAILURE:
            return "sigaction failure";
        case ERROR_CONTACTDB_FORK:
            return "fork failure";
        case ERROR_CONTACTDB_FORK_PARENT:
            return "fork parent exiting";
        case ERROR_CONTACTDB_SETSID:
            return "setsid error";
        case ERROR_CONTACTDB_GET_INVALID_SIZE:
            return "contactdb get invalid size";
        case ERROR_CONTACTDB_FULL:
            return "contactdb full";
        case ERROR_CONTACTDB_COUNT_MISMATCH:
            return "contactdb count mismatch";
        case ERROR_CTOOL_BAD_NUMBER:
            return "bad number";
        case ERROR_CTOOL_NUMBER_OUT_OF_RANGE:
            return "number out of range";
        case ERROR_CTOOL_INVALID_COMMAND:
            return "invalid command";
        case ERROR_CTOOL_CONNECT_FAILURE:
            return "connect failure";
        case ERROR_CONTACTDB_DROP_PRIVILEGES:
        case ERROR_CTOOL_DROP_PRIVILEGES:
            return "drop privileges";
        default:
            return "unknown error";
    }
}
