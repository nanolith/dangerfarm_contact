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
#define ERROR_DATABASE_PROTOCOL_INVALID_ID                   15
#define ERROR_DATABASE_SYNC                                  16
#define ERROR_DATABASE_ENV_CREATE                            17
#define ERROR_DATABASE_SET_MAPSIZE                           18
#define ERROR_DATABASE_SET_MAXDBS                            19
#define ERROR_DATABASE_ENV_OPEN                              20
#define ERROR_DATABASE_TXN_BEGIN                             21
#define ERROR_DATABASE_DBI_OPEN                              22
#define ERROR_DATABASE_TXN_COMMIT                            23
#define ERROR_DATABASE_PUT                                   24
#define ERROR_DATABASE_GET                                   25
#define ERROR_DATABASE_DELETE                                26
#define ERROR_DATABASE_CURSOR_OPEN                           27
#define ERROR_DATABASE_CURSOR_GET                            28
#define ERROR_CONTACTDB_MISSING_PARAMETER                    29
#define ERROR_CONTACTDB_BAD_PARAMETER                        30
#define ERROR_CONTACTDB_SOCKET_PATH_TOO_LONG                 31
#define ERROR_CONTACTDB_SOCKET_FAILURE                       32
#define ERROR_CONTACTDB_UNLINK_FAILURE                       33
#define ERROR_CONTACTDB_BIND_FAILURE                         34
#define ERROR_CONTACTDB_LISTEN_FAILURE                       35
#define ERROR_CONTACTDB_CHMOD_FAILURE                        36
#define ERROR_CONTACTDB_INVALID_ROLE                         37
#define ERROR_CONTACTDB_ACCEPT                               38
#define ERROR_CONTACTDB_PERMISSION_DENIED                    39
#define ERROR_CONTACTDB_SIGEMPTYSET_FAILURE                  40
#define ERROR_CONTACTDB_SIGACTION_FAILURE                    41
#define ERROR_CONTACTDB_FORK                                 42
#define ERROR_CONTACTDB_FORK_PARENT                          43
#define ERROR_CONTACTDB_SETSID                               44
#define ERROR_CONTACTDB_GET_INVALID_SIZE                     45
#define ERROR_CONTACTDB_FULL                                 46
#define ERROR_CONTACTDB_COUNT_MISMATCH                       47
#define ERROR_CONTACTDB_DROP_PRIVILEGES                      48
#define ERROR_CTOOL_BAD_PARAMETER                            49
#define ERROR_CTOOL_BAD_NUMBER                               50
#define ERROR_CTOOL_NUMBER_OUT_OF_RANGE                      51
#define ERROR_CTOOL_INVALID_COMMAND                          52
#define ERROR_CTOOL_SOCKET_PATH_TOO_LONG                     53
#define ERROR_CTOOL_SOCKET_FAILURE                           54
#define ERROR_CTOOL_CONNECT_FAILURE                          55
#define ERROR_CTOOL_DROP_PRIVILEGES                          56
#define ERROR_CONTACTFORM_INVALID_DROP_PRIVILEGES_STEP       57
#define ERROR_CONTACTFORM_DROP_PRIVILEGES                    58
#define ERROR_CONTACTFORM_SOCKETPAIR                         59
#define ERROR_CONTACTFORM_FORK                               60
#define ERROR_CONTACTFORM_SOCKET                             61
#define ERROR_CONTACTFORM_CONNECT                            62
#define ERROR_CONTACTFORM_DBSOCK_CLOSE                       63
#define ERROR_CONTACTFORM_DBPID_KILL                         64
#define ERROR_CONTACTFORM_DBPID_WAIT                         65
#define ERROR_CONTACTFORM_KHTTP_PARSE                        66
#define ERROR_CONTACTFORM_MISSING_FIELD                      67
#define ERROR_CONTACTFORM_KHTTP_HEAD                         68
#define ERROR_CONTACTFORM_KHTTP_BODY                         69
#define ERROR_CONTACTFORM_KHTTP_PUTS                         70

#define ERROR_INVALID_STATUS                             100000
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
