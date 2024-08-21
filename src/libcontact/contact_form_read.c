#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/util/socket.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_util_socket;
DANGERFARM_CONTACT_IMPORT_util_string;

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
    DANGERFARM_CONTACT_SYM(contact_form)** form, int s)
{
    int retval, release_retval;
    contact_form hdr;
    contact_form* tmp1 = NULL;
    contact_form* tmp2 = NULL;
    char* name = NULL;
    char* email = NULL;
    char* subject = NULL;
    char* comment = NULL;
    uint64_t size = 0;

    /* read the size. */
    retval = socket_read_uint64(&size, s);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* ensure the size is sane. */
    if (size < sizeof(contact_form) || size > MAX_CONTACT_FORM_SIZE)
    {
        retval = ERROR_CONTACT_FORM_INVALID;
        goto done;
    }

    /* read the contact form header. */
    retval = socket_read_contact_form_header(&hdr, s);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* verify the contact form header. */
    retval = contact_form_verify(&hdr, size);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* allocate memory for the contact form. */
    tmp1 = (contact_form*)malloc(size);
    if (NULL == tmp1)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* copy the header to the contact form. */
    tmp1->name_size = hdr.name_size;
    tmp1->email_size = hdr.email_size;
    tmp1->subject_size = hdr.subject_size;
    tmp1->comment_size = hdr.comment_size;

    /* compute the data size. */
    size_t data_size =
          tmp1->name_size + tmp1->email_size + tmp1->subject_size
        + tmp1->comment_size;

    /* the data size plus the contact form struct size equals size. */
    MODEL_ASSERT(size == data_size + sizeof(*tmp1));

    /* read the contact form data. */
    retval = socket_read_contact_form_data(tmp1->data, s, data_size);
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
    memset(&hdr, 0, sizeof(hdr));

    return retval;
}
