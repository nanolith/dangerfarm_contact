#pragma once
#include <stdint.h>

typedef struct contact_form contact_form;

/**
 * The contact form data used for storing, retrieving, and serializing contact
 * forms.
 */
struct contact_form
{
    uint64_t name_size;
    uint64_t email_size;
    uint64_t comment_size;
    char data[];
};

/**
 * \brief Create a \ref contact_form instance given a name, email, and comment.
 *
 * \param form          Pointer to the pointer to receive the form on success.
 * \param name          The name for this contact.
 * \param email         The email for this contact.
 * \param comment       The comment for this contact.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contact_form_create(
    contact_form** form, const char* name, const char* email,
    const char* comment);

/**
 * \brief Release a \ref contact_form instance.
 *
 * \param form          The \ref contact_form instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contact_form_release(contact_form* form);

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
int contact_form_extract_name(char** name, const contact_form* form);

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
int contact_form_extract_email(char** email, const contact_form* form);

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
int contact_form_extract_comment(char** comment, const contact_form* form);
