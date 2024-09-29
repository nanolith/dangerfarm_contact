#pragma once

#include <dangerfarm_contact/cbmc/function_contracts.h>
#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/contracts/properties/unix.h>
#include <dangerfarm_contact/function_decl.h>
#include <stdint.h>
#include <stddef.h>

#ifdef   __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* forward decls. */
typedef struct DANGERFARM_CONTACT_SYM(contact_form)
DANGERFARM_CONTACT_SYM(contact_form);

/**
 * \brief Write a uint32_t value to a socket.
 *
 * \param s             The socket to which the value is written.
 * \param val           The value to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_write_uint32)(int s, uint32_t val);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(socket_write_uint32),
    int s, uint32_t val)
        MODEL_ASSERT(prop_is_open_fd(s));
MODEL_CONTRACT_PRECONDITIONS_END(DANGERFARM_CONTACT_SYM(socket_write_uint32))

/**
 * \brief Write a uint64_t value to a socket.
 *
 * \param s             The socket to which the value is written.
 * \param val           The value to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_write_uint64)(int s, uint64_t val);

/**
 * \brief Read a uint32_t value from a socket.
 *
 * \param val           Pointer to the value to read.
 * \param s             The socket from which the value is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_read_uint32)(uint32_t* val, int s);

/**
 * \brief Read a uint64_t value from a socket.
 *
 * \param val           Pointer to the value to read.
 * \param s             The socket from which the value is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_read_uint64)(uint64_t* val, int s);

/**
 * \brief Write a contact form header to a socket.
 *
 *
 * \param s             The socket to which the value is written.
 * \param hdr           Pointer to the \ref contact_form header to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_write_contact_form_header)(
    int s, const DANGERFARM_CONTACT_SYM(contact_form)* hdr);

/**
 * \brief Read a contact form header from a socket.
 *
 * \note This reads the size data for the contact form, into a stack allocated
 * contact form header. The resulting form should NOT be released.
 *
 * \param hdr           Pointer to the \ref contact_form header to read.
 * \param s             The socket from which the value is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_read_contact_form_header)(
    DANGERFARM_CONTACT_SYM(contact_form)* hdr, int s);

/**
 * \brief Write contact form data to a socket.
 *
 * \param s             The socket to which this data is written.
 * \param data          Pointer to the data buffer to write.
 * \param size          The size of the data to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_write_contact_form_data)(
    int s, const char* data, size_t size);

/**
 * \brief Read contact form data from a socket.
 *
 * \note This read assumes that the backing buffer was already allocated by the
 * caller. This convenience method just makes model checking easier.
 *
 * \param data          Pointer to the data buffer to be populated by this read.
 * \param s             The socket from which this data is read.
 * \param size          The size of the data to read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(socket_read_contact_form_data)(
    char* data, int s, size_t size);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_socket_sym(sym) \
    DANGERFARM_CONTACT_BEGIN_EXPORT \
    static inline int sym ## socket_write_uint32( \
        int x, uint32_t y) { \
            return DANGERFARM_CONTACT_SYM(socket_write_uint32)(x,y); \
    } \
    static inline int sym ## socket_write_uint64( \
        int x, uint64_t y) { \
            return DANGERFARM_CONTACT_SYM(socket_write_uint64)(x,y); \
    } \
    static inline int sym ## socket_read_uint32( \
        uint32_t* x, int y) { \
            return DANGERFARM_CONTACT_SYM(socket_read_uint32)(x,y); \
    } \
    static inline int sym ## socket_read_uint64( \
        uint64_t* x, int y) { \
            return DANGERFARM_CONTACT_SYM(socket_read_uint64)(x,y); \
    } \
    static inline int sym ## socket_write_contact_form_header( \
        int x, const DANGERFARM_CONTACT_SYM(contact_form)* y) { \
            return DANGERFARM_CONTACT_SYM( \
                socket_write_contact_form_header)(x,y); \
    } \
    static inline int sym ## socket_read_contact_form_header( \
        DANGERFARM_CONTACT_SYM(contact_form)* x, int y) { \
            return DANGERFARM_CONTACT_SYM( \
                socket_read_contact_form_header)(x,y); \
    } \
    static inline int sym ## socket_write_contact_form_data( \
        int x, const char* y, size_t z) { \
            return DANGERFARM_CONTACT_SYM( \
                        socket_write_contact_form_data)(x,y,z); \
    } \
    static inline int sym ## socket_read_contact_form_data( \
        char* x, int y, size_t z) { \
            return DANGERFARM_CONTACT_SYM( \
                socket_read_contact_form_data)(x,y,z); \
    } \
    DANGERFARM_CONTACT_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define DANGERFARM_CONTACT_IMPORT_util_socket_as(sym) \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_socket_sym(sym ## _)
#define DANGERFARM_CONTACT_IMPORT_util_socket \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_socket_sym()

#ifdef   __cplusplus
}
#endif /*__cplusplus*/
