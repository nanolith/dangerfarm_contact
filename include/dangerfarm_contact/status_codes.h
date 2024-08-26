#pragma once

#ifdef   __cplusplus
extern "C" {
#endif /*__cplusplus*/

#define STATUS_SUCCESS                                        0
#define ERROR_GENERAL_OUT_OF_MEMORY                           1
#define ERROR_READ_MULTIBYTE_EOF                              2
#define ERROR_READ_MULTIBYTE_RAW_CONTINUATION                 3
#define ERROR_READ_MULTIBYTE_INVALID_CONTINUATION             4
#define ERROR_READ_MULTIBYTE_OVERLONG_REPRESENTATION          5
#define ERROR_READ_MULTIBYTE_UNEXPECTED_CHARACTER             6
#define ERROR_READ_MULTIBYTE_CODEPOINT_OUT_OF_RANGE           7
#define ERROR_CONTACT_FORM_WRITE                              8
#define ERROR_CONTACT_FORM_READ                               9
#define ERROR_CONTACT_FORM_INVALID                           10
#define ERROR_SOCKET_WRITE                                   11
#define ERROR_SOCKET_READ                                    12
#define ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID        13
#define ERROR_DATABASE_PROTOCOL_INVALID_COUNT                14
#define ERROR_DATABASE_SYNC                                  15
#define ERROR_DATABASE_ENV_CREATE                            16
#define ERROR_DATABASE_SET_MAPSIZE                           17
#define ERROR_DATABASE_SET_MAXDBS                            18
#define ERROR_DATABASE_ENV_OPEN                              19
#define ERROR_DATABASE_TXN_BEGIN                             20
#define ERROR_DATABASE_DBI_OPEN                              21
#define ERROR_DATABASE_TXN_COMMIT                            22
#define ERROR_DATABASE_PUT                                   23
#define ERROR_DATABASE_GET                                   24
#define ERROR_DATABASE_DELETE                                25
#define ERROR_DATABASE_CURSOR_OPEN                           26
#define ERROR_DATABASE_CURSOR_GET                            27
#define ERROR_CONTACTDB_MISSING_PARAMETER                    28
#define ERROR_CONTACTDB_BAD_PARAMETER                        29
#define ERROR_CONTACTDB_SOCKET_PATH_TOO_LONG                 30
#define ERROR_CONTACTDB_SOCKET_FAILURE                       31
#define ERROR_CONTACTDB_UNLINK_FAILURE                       32
#define ERROR_CONTACTDB_BIND_FAILURE                         33
#define ERROR_CONTACTDB_LISTEN_FAILURE                       34
#define ERROR_CONTACTDB_CHMOD_FAILURE                        35
#define ERROR_CONTACTDB_INVALID_ROLE                         36
#define ERROR_CONTACTDB_ACCEPT                               37
#define ERROR_CONTACTDB_PERMISSION_DENIED                    38
#define ERROR_CONTACTDB_SIGACTION_FAILURE                    39
#define ERROR_CONTACTDB_FORK                                 40
#define ERROR_CONTACTDB_FORK_PARENT                          41
#define ERROR_CONTACTDB_SETSID                               42
#define ERROR_CONTACTDB_GET_INVALID_SIZE                     43
#define ERROR_CONTACTDB_FULL                                 44
#define ERROR_CONTACTDB_COUNT_MISMATCH                       45
#define ERROR_CONTACTDB_DROP_PRIVILEGES                      46
#define ERROR_CTOOL_BAD_PARAMETER                            47
#define ERROR_CTOOL_BAD_NUMBER                               48
#define ERROR_CTOOL_NUMBER_OUT_OF_RANGE                      49
#define ERROR_CTOOL_INVALID_COMMAND                          50
#define ERROR_CTOOL_SOCKET_PATH_TOO_LONG                     51
#define ERROR_CTOOL_SOCKET_FAILURE                           52
#define ERROR_CTOOL_CONNECT_FAILURE                          53
#define ERROR_CTOOL_DROP_PRIVILEGES                          54
#define ERROR_CONTACTFORM_INVALID_DROP_PRIVILEGES_STEP       55
#define ERROR_CONTACTFORM_DROP_PRIVILEGES                    56
#define ERROR_CONTACTFORM_SOCKETPAIR                         57
#define ERROR_CONTACTFORM_FORK                               58
#define ERROR_CONTACTFORM_SOCKET                             59
#define ERROR_CONTACTFORM_CONNECT                            60
#define ERROR_CONTACTFORM_DBSOCK_CLOSE                       61
#define ERROR_CONTACTFORM_DBPID_KILL                         62
#define ERROR_CONTACTFORM_DBPID_WAIT                         63
#define ERROR_CONTACTFORM_KHTTP_PARSE                        64
#define ERROR_CONTACTFORM_MISSING_FIELD                      65
#define ERROR_CONTACTFORM_KHTTP_HEAD                         66
#define ERROR_CONTACTFORM_KHTTP_BODY                         67
#define ERROR_CONTACTFORM_KHTTP_PUTS                         68

/**
 * \brief Return a description string for a given status code.
 *
 * \param status            The status code to decode.
 *
 * \returns a string representing this status code, or an error string if it is
 * unknown.
 */
const char* status_decode(int status);

#ifdef   __cplusplus
}
#endif /*__cplusplus*/
