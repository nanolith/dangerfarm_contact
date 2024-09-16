#pragma once
#include <dangerfarm_contact/cbmc/function_contracts.h>
#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/function_decl.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef   __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* don't allow contact forms larger than 1 MB. */
#define MAX_CONTACT_FORM_SIZE  (1024 * 1024)

typedef struct DANGERFARM_CONTACT_SYM(contact_form)
DANGERFARM_CONTACT_SYM(contact_form);

/**
 * The contact form data used for storing, retrieving, and serializing contact
 * forms.
 */
struct DANGERFARM_CONTACT_SYM(contact_form)
{
    uint64_t name_size;
    uint64_t email_size;
    uint64_t subject_size;
    uint64_t comment_size;
    char data[];
};

/**
 * \brief Model check helper to determine whether a contact form appears valid.
 *
 * \param form          The contact form to check.
 *
 * \returns true if the contact form appears valid and false otherwise.
 */
bool DANGERFARM_CONTACT_SYM(prop_valid_contact_form)(
    const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Create a \ref contact_form instance given a name, email, and comment.
 *
 * \param form          Pointer to the pointer to receive the form on success.
 * \param name          The name for this contact.
 * \param email         The email for this contact.
 * \param subject       The subject for this contact.
 * \param comment       The comment for this contact.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_create)(
    DANGERFARM_CONTACT_SYM(contact_form)** form, const char* name,
    const char* email, const char* subject, const char* comment);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(contact_form_create),
    DANGERFARM_CONTACT_SYM(contact_form)** form, const char* name,
    const char* email, const char* subject, const char* comment)
        MODEL_ASSERT(NULL != form);
        MODEL_ASSERT(DANGERFARM_CONTACT_SYM(prop_string_valid)(name));
        MODEL_ASSERT(DANGERFARM_CONTACT_SYM(prop_string_valid)(email));
        MODEL_ASSERT(DANGERFARM_CONTACT_SYM(prop_string_valid)(subject));
        MODEL_ASSERT(DANGERFARM_CONTACT_SYM(prop_string_valid)(comment));
MODEL_CONTRACT_PRECONDITIONS_END(DANGERFARM_CONTACT_SYM(contact_form_create))

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    DANGERFARM_CONTACT_SYM(contact_form_create),
    DANGERFARM_CONTACT_SYM(contact_form)** form, int retval, const char* name,
    const char* email, const char* subject, const char* comment)
        if (STATUS_SUCCESS == retval)
        {
            MODEL_ASSERT(
                DANGERFARM_CONTACT_SYM(prop_valid_contact_form)(*form));
        }
        else
        {
            MODEL_ASSERT(NULL == *form);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(DANGERFARM_CONTACT_SYM(contact_form_create))

/**
 * \brief Release a \ref contact_form instance.
 *
 * \param form          The \ref contact_form instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_release)(
    DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Read a \ref contact_form from the given descriptor.
 *
 * \param form          Pointer to the pointer to receive the form on success.
 * \param s             The descriptor from which this form is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_read)(
    DANGERFARM_CONTACT_SYM(contact_form)** form, int s);

/**
 * \brief Write a \ref contact_form to the given descriptor.
 *
 * \param s             The descriptor to which the \ref contact_form is
 *                      written.
 * \param form          The \ref contact_form to write.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_write)(
    int s, const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Given a serialized contact form and a size, verify that the contact
 * form is valid (i.e. that offsets are correct wrt size.)
 *
 * \param form          The contact form to verify.
 * \param size          The size of the contact form to verify.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_verify)(
    const DANGERFARM_CONTACT_SYM(contact_form)* form, size_t size);

/**
 * \brief Given a valid \ref contact_form, compute the size.
 *
 * \param form          The contact form for this operation.
 *
 * \returns the size of this form.
 */
size_t DANGERFARM_CONTACT_SYM(contact_form_compute_size)(
    const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Given a \ref contact_form, extract the name as a string.
 *
 * \note This string is owned by the caller and must be reclaimed using \ref
 * string_release.
 *
 * \param name          Pointer to the char pointer to receive the name on
 *                      success.
 * \param form          The \ref contact_form instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_extract_name)(
    char** name, const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Given a \ref contact_form, extract the email as a string.
 *
 * \note This string is owned by the caller and must be reclaimed using \ref
 * string_release.
 *
 * \param email         Pointer to the char pointer to receive the email on
 *                      success.
 * \param form          The \ref contact_form instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_extract_email)(
    char** email, const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Given a \ref contact_form, extract the subject as a string.
 *
 * \note This string is owned by the caller and must be reclaimed using \ref
 * string_release.
 *
 * \param subject       Pointer to the char pointer to receive the subject on
 *                      success.
 * \param form          The \ref contact_form instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_extract_subject)(
    char** subject, const DANGERFARM_CONTACT_SYM(contact_form)* form);

/**
 * \brief Given a \ref contact_form, extract the comment as a string.
 *
 * \note This string is owned by the caller and must be reclaimed using \ref
 * string_release.
 *
 * \param comment       Pointer to the char pointer to receive the comment on
 *                      success.
 * \param form          The \ref contact_form instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(contact_form_extract_comment)(
    char** comment, const DANGERFARM_CONTACT_SYM(contact_form)* form);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_DANGERFARM_CONTACT_IMPORT_contact_form_sym(sym) \
    DANGERFARM_CONTACT_BEGIN_EXPORT \
    typedef DANGERFARM_CONTACT_SYM(contact_form) sym ## contact_form; \
    static inline int sym ## contact_form_create( \
        DANGERFARM_CONTACT_SYM(contact_form)** v, const char* w, \
        const char* x, const char* y, const char* z) { \
            return DANGERFARM_CONTACT_SYM(contact_form_create)(v,w,x,y,z); \
    } \
    static inline int sym ## contact_form_release( \
        DANGERFARM_CONTACT_SYM(contact_form)* x) { \
            return DANGERFARM_CONTACT_SYM(contact_form_release)(x); \
    } \
    static inline int sym ## contact_form_read( \
        DANGERFARM_CONTACT_SYM(contact_form)** x, int y) { \
            return DANGERFARM_CONTACT_SYM(contact_form_read)(x,y); \
    } \
    static inline int sym ## contact_form_write( \
        int x, const DANGERFARM_CONTACT_SYM(contact_form)* y) { \
            return DANGERFARM_CONTACT_SYM(contact_form_write)(x,y); \
    } \
    static inline int sym ## contact_form_verify( \
        const DANGERFARM_CONTACT_SYM(contact_form)* x, size_t y) { \
            return DANGERFARM_CONTACT_SYM(contact_form_verify)(x,y); \
    } \
    static inline size_t sym ## contact_form_compute_size( \
        const DANGERFARM_CONTACT_SYM(contact_form)* x) { \
            return DANGERFARM_CONTACT_SYM(contact_form_compute_size)(x); \
    } \
    static inline int sym ## contact_form_extract_name( \
        char** x, const DANGERFARM_CONTACT_SYM(contact_form)* y) { \
            return DANGERFARM_CONTACT_SYM(contact_form_extract_name)(x,y); \
    } \
    static inline int sym ## contact_form_extract_email( \
        char** x, const DANGERFARM_CONTACT_SYM(contact_form)* y) { \
            return DANGERFARM_CONTACT_SYM(contact_form_extract_email)(x,y); \
    } \
    static inline int sym ## contact_form_extract_subject( \
        char** x, const DANGERFARM_CONTACT_SYM(contact_form)* y) { \
            return  DANGERFARM_CONTACT_SYM(contact_form_extract_subject)(x,y); \
    } \
    static inline int sym ## contact_form_extract_comment( \
        char** x, const DANGERFARM_CONTACT_SYM(contact_form)* y) { \
            return DANGERFARM_CONTACT_SYM(contact_form_extract_comment)(x,y); \
    } \
    static inline bool sym ## prop_valid_contact_form( \
        const DANGERFARM_CONTACT_SYM(contact_form)* x) { \
            return DANGERFARM_CONTACT_SYM(prop_valid_contact_form)(x); \
    } \
    DANGERFARM_CONTACT_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define DANGERFARM_CONTACT_IMPORT_contact_form_as(sym) \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_contact_form_sym(sym ## _)
#define DANGERFARM_CONTACT_IMPORT_contact_form \
    __INTERNAL_DANGERFARM_CONTACT_IMPORT_contact_form_sym()

#ifdef   __cplusplus
}
#endif /*__cplusplus*/
