#pragma once

#include <dangerfarm_contact/cbmc/function_contracts.h>
#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/function_decl.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifdef   __cplusplus
extern "C" {
#endif /*__cplusplus*/

/**
 * \brief Model check helper to determine whether a string appears valid.
 *
 * \param str           The string to check.
 *
 * \returns true if the string appears valid and false otherwise.
 */
bool DANGERFARM_CONTACT_SYM(prop_string_valid)(const char* str);

/**
 * \brief Create a string from a data pointer and size.
 *
 * \note Any null bytes in the data will be changed to ' ' to ensure that the
 * string can be fully read.
 *
 * \param str           Pointer to the character pointer for this string to set
 *                      on success.
 * \param data          Pointer to the data for this string.
 * \param size          The size of this data. The resulting string will be
 *                      size + 1 to account for the ASCII zero.
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(string_create)(
    char** str, const void* data, size_t size);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(string_create),
    char** str, const void* data, size_t size)
        MODEL_ASSERT(NULL != str);
        MODEL_ASSERT(NULL != data);
        MODEL_CHECK_OBJECT_READ(data, size);
MODEL_CONTRACT_PRECONDITIONS_END(DANGERFARM_CONTACT_SYM(string_create))

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(string_create), int retval, char** str, size_t size)
        if (STATUS_SUCCESS == retval)
        {
            MODEL_ASSERT(DANGERFARM_CONTACT_SYM(prop_string_valid)(*str));
            MODEL_CHECK_OBJECT_READ(*str, size + 1);
        }
        else
        {
            MODEL_ASSERT(NULL == *str);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(DANGERFARM_CONTACT_SYM(string_create))

/**
 * \brief Filter a string, replacing any invalid UTF-8 sequences or HTML /
 * commandline unsafe sequences with spaces.
 *
 * \param str           The string to filter.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
DANGERFARM_CONTACT_SYM(string_filter)(char* str);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(string_filter), char* str)
        MODEL_ASSERT(NULL != str);
        MODEL_ASSERT(DANGERFARM_CONTACT_SYM(prop_string_valid)(str));
        MODEL_CHECK_OBJECT_RW(str, strlen(str));
MODEL_CONTRACT_PRECONDITIONS_END(DANGERFARM_CONTACT_SYM(string_filter))

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(string_filter), int retval, char* str)
        MODEL_ASSERT(DANGERFARM_CONTACT_SYM(prop_string_valid)(str));
        MODEL_CHECK_OBJECT_RW(str, strlen(str));
MODEL_CONTRACT_POSTCONDITIONS_END(DANGERFARM_CONTACT_SYM(string_filter))

/**
 * \brief Given an allocated string, clear and release it.
 *
 * \param str           The string to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(string_release)(char* str);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(string_release), char* str)
        MODEL_ASSERT(NULL != str);
        MODEL_ASSERT(DANGERFARM_CONTACT_SYM(prop_string_valid)(str));
        MODEL_CHECK_OBJECT_RW(str, strlen(str));
MODEL_CONTRACT_PRECONDITIONS_END(DANGERFARM_CONTACT_SYM(string_release))

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(string_release), int retval, char* str)
MODEL_CONTRACT_POSTCONDITIONS_END(DANGERFARM_CONTACT_SYM(string_release))

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_string_sym(sym) \
    DANGERFARM_CONTACT_BEGIN_EXPORT \
    static inline int sym ## string_create( \
        char** x, const void* y, size_t z) { \
            return DANGERFARM_CONTACT_SYM(string_create)(x,y,z); \
    } \
    static inline int sym ## string_filter( \
        char* x) { \
            return DANGERFARM_CONTACT_SYM(string_filter)(x); \
    } \
    static inline int sym ## string_release(char* x) { \
        return DANGERFARM_CONTACT_SYM(string_release)(x); \
    } \
    static inline bool sym ## prop_string_valid(const char* x) { \
        return DANGERFARM_CONTACT_SYM(prop_string_valid)(x); \
    } \
    DANGERFARM_CONTACT_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define DANGERFARM_CONTACT_IMPORT_util_string_as(sym) \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_string_sym(sym ## _)
#define DANGERFARM_CONTACT_IMPORT_util_string \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_string_sym()

#ifdef   __cplusplus
}
#endif /*__cplusplus*/
