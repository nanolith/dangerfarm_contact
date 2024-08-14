#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <stdlib.h>
#include <string.h>

DANGERFARM_CONTACT_IMPORT_contact_form;

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
int contact_form_create(
    contact_form** form, const char* name, const char* email,
    const char* subject, const char* comment)
{
    contact_form* tmp = NULL;
    size_t offset = 0;
    size_t name_len = strlen(name);
    size_t email_len = strlen(email);
    size_t subject_len = strlen(subject);
    size_t comment_len = strlen(comment);
    size_t contact_form_size = sizeof(contact_form);
    size_t total_size =
        name_len + email_len + subject_len + comment_len + contact_form_size;

    /* allocate memory for the form. */
    tmp = (contact_form*)malloc(total_size);
    if (NULL == tmp)
    {
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* clear memory. */
    memset(tmp, 0, total_size);

    /* set the sizes. */
    tmp->name_size = name_len;
    tmp->email_size = email_len;
    tmp->subject_size = subject_len;
    tmp->comment_size = comment_len;

    /* copy the strings. */
    memcpy(tmp->data + offset, name, name_len);         offset += name_len;
    memcpy(tmp->data + offset, email, email_len);       offset += email_len;
    memcpy(tmp->data + offset, subject, subject_len);   offset += subject_len;
    memcpy(tmp->data + offset, comment, comment_len);   offset += comment_len;

    /* success. */
    *form = tmp;
    return STATUS_SUCCESS;
}
