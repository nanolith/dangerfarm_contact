#pragma once

#include <dangerfarm_contact/function_decl.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef   __cplusplus
extern "C" {
#endif /*__cplusplus*/

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
int string_create(char** str, const void* data, size_t size);

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
int string_filter(char* str);

/**
 * \brief Given an allocated string, clear and release it.
 *
 * \param str           The string to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int string_release(char* str);

/**
 * \brief Model check helper to determine whether a string appears valid.
 *
 * \param str           The string to check.
 *
 * \returns true if the string appears valid and false otherwise.
 */
bool prop_string_valid(const char* str);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_string_sym(sym) \
    DANGERFARM_CONTACT_BEGIN_EXPORT \
    DANGERFARM_CONTACT_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define DANGERFARM_CONTACT_IMPORT_util_string_as(sym) \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_string_sym(sym ## _)
#define DANGERFARM_CONTACT_IMPORT_util_string \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_util_string_sym()

#ifdef   __cplusplus
}
#endif /*__cplusplus*/
