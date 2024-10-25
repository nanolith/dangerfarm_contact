#pragma once

#include <dangerfarm_contact/function_decl.h>
#include <stdint.h>

#ifdef   __cplusplus
extern "C" {
#endif /*__cplusplus*/

typedef struct DANGERFARM_CONTACT_SYM(contact_form)
DANGERFARM_CONTACT_SYM(contact_form);

enum DANGERFARM_CONTACT_SYM(database_protocol_request_id)
{
    DATABASE_REQUEST_ID_CONTACT_FORM_APPEND                             = 1,
    DATABASE_REQUEST_ID_CONTACT_FORM_GET_COUNT                          = 2,
    DATABASE_REQUEST_ID_CONTACT_FORM_GET_LIST                           = 3,
    DATABASE_REQUEST_ID_CONTACT_FORM_GET                                = 4,
    DATABASE_REQUEST_ID_CONTACT_FORM_DELETE                             = 6,
    DATABASE_REQUEST_ID_TRUNCATE                                        = 7,
};

#define DATABASE_PROTOCOL_MAX_COUNT         1024

/**
 * \brief Read a database request id from the socket.
 *
 * \param req       The request to read.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(database_read_request_id)(uint32_t* req, int s);

/**
 * \brief Write a contact form append request to the socket.
 *
 * \param s         The socket to which this request is written.
 * \param form      The contact form to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(database_write_contact_form_append_request)(
    int s, const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Read a contact form append request payload.
 *
 * \note On success, the contact form is owned by the caller and must be
 * released when no longer needed.
 *
 * \param form      Pointer to the contact form append request payload to be
 *                  updated with the created payload on success.
 * \param s         The socket from which this request payload is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(database_read_contact_form_append_request_payload)(
    DANGERFARM_CONTACT_SYM(contact_form)** form, int s);

/**
 * \brief Write a contact form append response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(database_write_contact_form_append_response)(
    int s, const uint32_t status);

/**
 * \brief Read a contact form append response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param s         The socket from which this response is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(database_read_contact_form_append_response)(
    uint32_t* status, int s);

/**
 * \brief Write a get count request to the socket.
 *
 * \param s         The socket to which this request is written.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(database_write_contact_form_get_count_request)(
    int s);

/**
 * \brief Write a contact form get count response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status code to write.
 * \param count     The count to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(database_write_contact_form_get_count_response)(
    int s, const uint32_t status, const uint64_t count);

/**
 * \brief Read a contact form get count response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param count     Pointer to receive the count on success.
 * \param s         The socket from which this response is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_get_count_response)(
    uint32_t* status, uint64_t* count, int s);

/**
 * \brief Write a list contact forms request to the socket.
 *
 * \param s         The socket to which this request is written.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_list_request)(int s);

/**
 * \brief Write a list contact forms response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this response.
 * \param count     The count of the id list.
 * \param id_list   The id list to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_list_response)(
    int s, const uint32_t status, const uint64_t count,
    const uint64_t* id_list);

/**
 * \brief Read a list contact forms response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param count     Pointer to receive the count of items to be read.
 * \param id_list   Pointer to receive the array of contact IDs.
 * \param s         The socket from which this response is read.
 *
 * \note id_list is updated with a dynamically allocated array which is owned
 * by the caller on success.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_list_response)(
    uint32_t* status, uint64_t* count, uint64_t** id_list, int s);

/**
 * \brief Write a contact read request to the socket.
 *
 * \param s         The socket to which this request is written.
 * \param id        The id of the contact form to be read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_read_request)(
    int s, uint64_t id);

/**
 * \brief Read a contact read request payload from the socket.
 *
 * \param id        Pointer to receive the contact form id on success.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_read_request_payload)(
    uint64_t* id, int s);

/**
 * \brief Write a contact read response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this response.
 * \param form      The contact form to write to the socket.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_read_response)(
    int s, const uint32_t status,
    const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Read a contact read response from the socket.
 *
 * \note The form pointer is populated only if this function returns success AND
 * the status is set to success.
 *
 * \param status    The status for this response.
 * \param form      Pointer to the form pointer to get a created form instance
 *                  on success.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_read_response)(
    uint32_t* status, DANGERFARM_CONTACT_SYM(contact_form)** form, int s);

/**
 * \brief Write a contact delete request to the socket.
 *
 * \param s         The socket to which this request is written.
 * \param id        The id of the contact form to be deleted.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_delete_request)(
    int s, uint64_t id);

/**
 * \brief Read a contact delete request payload from the socket.
 *
 * \param id        Pointer to receive the contact form id on success.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_delete_request_payload)(
    uint64_t* id, int s);

/**
 * \brief Write a contact delete response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this response.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_delete_response)(
    int s, const uint32_t status);

/**
 * \brief Read a contact delete response from the socket.
 *
 * \param status    The status for this request.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_contact_form_delete_response)(
    uint32_t* status, int s);

/**
 * \brief Write a database truncate request to the socket.
 *
 * \param s         The socket to which this request is written.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_database_truncate_request)(int s);

/**
 * \brief Write a database truncate response to the socket.
 *
 * \param s         The socket to which this response is written.
 * \param status    The status for this response.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_database_truncate_response)(
    int s, const uint32_t status);

/**
 * \brief Read a database truncate response from the socket.
 *
 * \param status    The status for this response.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_database_truncate_response)(
    uint32_t* status, int s);

/**
 * \brief Write a generic response to the socket.
 *
 * \param s         The socket from which this request is read.
 * \param req       The request id for this response.
 * \param status    The status for this response.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_generic_response)(
    int s, uint32_t req, uint32_t status);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_DANGERFARM_CONTACT_IMPORT_protocol_database_sym(sym) \
    DANGERFARM_CONTACT_BEGIN_EXPORT \
    static inline int sym ## database_read_request_id( \
        uint32_t* x, int y) { \
            return DANGERFARM_CONTACT_SYM(database_read_request_id)(x, y); \
    } \
    static inline int sym ## database_write_contact_form_append_request( \
        int x, const DANGERFARM_CONTACT_SYM(contact_form)* y) { \
            return DANGERFARM_CONTACT_SYM( \
                        database_write_contact_form_append_request)(x,y); \
    } \
    static inline int \
    sym ## database_read_contact_form_append_request_payload( \
        DANGERFARM_CONTACT_SYM(contact_form)** x, int y) { \
            return  DANGERFARM_CONTACT_SYM( \
                        database_read_contact_form_append_request_payload)( \
                            x,y); \
    } \
    static inline int sym ## database_write_contact_form_append_response( \
        int x, const uint32_t y) { \
            return  DANGERFARM_CONTACT_SYM( \
                database_write_contact_form_append_response)(x,y); \
    } \
    static inline int sym ## database_read_contact_form_append_response( \
        uint32_t* x, int y) { \
            return DANGERFARM_CONTACT_SYM( \
                        database_read_contact_form_append_response)(x,y); \
    } \
    static inline int sym ## database_write_contact_form_get_count_request( \
        int x) { \
            return DANGERFARM_CONTACT_SYM( \
                        database_write_contact_form_get_count_request)(x); \
    } \
    static inline int sym ## database_write_contact_form_get_count_response( \
        int x, const uint32_t y, const uint64_t z) { \
            return DANGERFARM_CONTACT_SYM( \
                        database_write_contact_form_get_count_response)( \
                            x,y,z); \
    } \
    static inline int sym ## database_read_contact_form_get_count_response( \
        uint32_t* x, uint64_t* y, int z) { \
            return DANGERFARM_CONTACT_SYM( \
                database_read_contact_form_get_count_response)(x,y,z); \
    } \
    static inline int sym ## database_write_contact_form_list_request(int x) { \
        return DANGERFARM_CONTACT_SYM( \
            database_write_contact_form_list_request)(x); \
    } \
    static inline int sym ## database_write_contact_form_list_response( \
        int w, const uint32_t x, const uint64_t y, const uint64_t* z) { \
        return DANGERFARM_CONTACT_SYM( \
            database_write_contact_form_list_response)(w,x,y,z); \
    } \
    static inline int sym ## database_read_contact_form_list_response( \
        uint32_t* w, uint64_t* x, uint64_t** y, int z) { \
        return DANGERFARM_CONTACT_SYM( \
            database_read_contact_form_list_response)(w,x,y,z); \
    } \
    static inline int sym ## database_write_contact_form_read_request( \
        int x, uint64_t y) { \
        return DANGERFARM_CONTACT_SYM( \
            database_write_contact_form_read_request)(x,y); \
    } \
    static inline int sym ## database_read_contact_form_read_request_payload( \
        uint64_t* x, int y) { \
        return DANGERFARM_CONTACT_SYM( \
            database_read_contact_form_read_request_payload)(x, y); \
    } \
    static inline int sym ## database_write_contact_form_read_response( \
        int x, const uint32_t y, \
        const DANGERFARM_CONTACT_SYM(contact_form)* z) { \
            return DANGERFARM_CONTACT_SYM( \
                database_write_contact_form_read_response)(x,y,z); \
    } \
    static inline int sym ## database_read_contact_form_read_response( \
        uint32_t* x, DANGERFARM_CONTACT_SYM(contact_form)** y, int z) { \
            return DANGERFARM_CONTACT_SYM( \
                database_read_contact_form_read_response)(x,y,z); \
    } \
    static inline int sym ## database_write_contact_form_delete_request( \
        int x, uint64_t y) { \
            return DANGERFARM_CONTACT_SYM( \
                database_write_contact_form_delete_request)(x,y); \
    } \
    static inline int \
    sym ## database_read_contact_form_delete_request_payload( \
        uint64_t* x, int y) { \
            return DANGERFARM_CONTACT_SYM( \
                database_read_contact_form_delete_request_payload)(x,y); \
    } \
    static inline int sym ## database_write_contact_form_delete_response( \
        int x, const uint32_t y) { \
            return DANGERFARM_CONTACT_SYM( \
                database_write_contact_form_delete_response)(x,y); \
    } \
    static inline int sym ## database_read_contact_form_delete_response( \
        uint32_t* x, int y) { \
            return DANGERFARM_CONTACT_SYM( \
                database_read_contact_form_delete_response)(x,y); \
    } \
    static inline int \
    sym ## database_write_database_truncate_request(int x) { \
        return DANGERFARM_CONTACT_SYM( \
            database_write_database_truncate_request)(x); \
    } \
    static inline int sym ## database_write_database_truncate_response( \
        int x, const uint32_t y) { \
        return DANGERFARM_CONTACT_SYM( \
            database_write_database_truncate_response)(x,y); \
    } \
    static inline int sym ## database_read_database_truncate_response( \
        uint32_t* x, int y) { \
        return DANGERFARM_CONTACT_SYM( \
            database_read_database_truncate_response)(x,y); \
    } \
    static inline int sym ## database_write_generic_response( \
        int x, uint32_t y, uint32_t z) { \
            return DANGERFARM_CONTACT_SYM( \
                        database_write_generic_response)(x,y,z); \
    } \
    DANGERFARM_CONTACT_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define DANGERFARM_CONTACT_IMPORT_protocol_database_as(sym) \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_protocol_database_sym(sym ## _)
#define DANGERFARM_CONTACT_IMPORT_protocol_database \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_protocol_database_sym()

#ifdef   __cplusplus
}
#endif /*__cplusplus*/
