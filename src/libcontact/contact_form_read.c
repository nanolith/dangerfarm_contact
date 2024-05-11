#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
int contact_form_read(contact_form** form, int s)
{
    int retval, release_retval;
    contact_form* tmp1 = NULL;
    contact_form* tmp2 = NULL;
    char* name = NULL;
    char* email = NULL;
    char* subject = NULL;
    char* comment = NULL;
    ssize_t read_bytes = 0;
    size_t size = 0;

    /* read the size. */
    read_bytes = read(s, &size, sizeof(size));
    if (read_bytes < 0 || (size_t)read_bytes != sizeof(size))
    {
        retval = ERROR_CONTACT_FORM_READ;
        goto done;
    }

    /* ensure the size is sane. */
    if (size < sizeof(contact_form) || size > MAX_CONTACT_FORM_SIZE)
    {
        retval = ERROR_CONTACT_FORM_INVALID;
        goto done;
    }

    /* allocate memory for the contact form. */
    tmp1 = (contact_form*)malloc(size);
    if (NULL == tmp1)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* read the contact form. */
    read_bytes = read(s, tmp1, size);
    if (read_bytes < 0 || (size_t)read_bytes != size)
    {
        retval = ERROR_CONTACT_FORM_READ;
        goto cleanup_tmp1;
    }

    /* verify the contact form. */
    retval = contact_form_verify(tmp1, size);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp1;
    }

    /* extract name from the contact form. */
    retval = contact_form_extract_name(&name, tmp1);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp1;
    }

    /* extract email from the contact form. */
    retval = contact_form_extract_email(&email, tmp1);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_name;
    }

    /* extract subject from the contact form. */
    retval = contact_form_extract_subject(&subject, tmp1);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_email;
    }

    /* extract comment from the contact form. */
    retval = contact_form_extract_comment(&comment, tmp1);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_subject;
    }

    /* filter name. */
    retval = string_filter(name);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_comment;
    }

    /* filter email. */
    retval = string_filter(email);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_comment;
    }

    /* filter subject. */
    retval = string_filter(subject);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_comment;
    }

    /* filter comment. */
    retval = string_filter(comment);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_comment;
    }

    /* create a filtered contact form. */
    retval = contact_form_create(&tmp2, name, email, subject, comment);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_comment;
    }

    /* success. */
    *form = tmp2;
    retval = STATUS_SUCCESS;
    goto cleanup_comment;

cleanup_comment:
    release_retval = string_release(comment);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_subject:
    release_retval = string_release(subject);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_email:
    release_retval = string_release(email);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_name:
    release_retval = string_release(name);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

cleanup_tmp1:
    memset(tmp1, 0, size);
    free(tmp1);

done:
    return retval;
}
