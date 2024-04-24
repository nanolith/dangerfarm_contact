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
 * \brief Create a contact form instance given a name, email, and comment.
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
