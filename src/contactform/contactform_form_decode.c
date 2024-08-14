#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>

#include "contactform_internal.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

/**
 * \brief Decode a contact form instance using form data.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_form_decode(contactform_context* ctx)
{
    int retval;
    char* name = NULL;
    char* email = NULL;
    char* subject = NULL;
    char* comment = NULL;

    /* verify that the name field was parsed. */
    if (NULL == ctx->req.fieldmap[KEY_NAME])
    {
        retval = ERROR_CONTACTFORM_MISSING_FIELD;
        goto done;
    }

    /* copy name. */
    name = strdup(ctx->req.fieldmap[KEY_NAME]->val);
    if (NULL == name)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* filter name. */
    retval = string_filter(name);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_name;
    }

    /* verify that the email field was parsed. */
    if (NULL == ctx->req.fieldmap[KEY_EMAIL])
    {
        retval = ERROR_CONTACTFORM_MISSING_FIELD;
        goto cleanup_name;
    }

    /* copy email. */
    email = strdup(ctx->req.fieldmap[KEY_EMAIL]->val);
    if (NULL == email)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto cleanup_name;
    }

    /* filter email. */
    retval = string_filter(email);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_email;
    }

    /* verify that the subject field was parsed. */
    if (NULL == ctx->req.fieldmap[KEY_SUBJECT])
    {
        retval = ERROR_CONTACTFORM_MISSING_FIELD;
        goto cleanup_email;
    }

    /* copy subject. */
    subject = strdup(ctx->req.fieldmap[KEY_SUBJECT]->val);
    if (NULL == subject)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto cleanup_email;
    }

    /* filter subject. */
    retval = string_filter(subject);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_subject;
    }

    /* verify that the comment field was parsed. */
    if (NULL == ctx->req.fieldmap[KEY_COMMENT])
    {
        retval = ERROR_CONTACTFORM_MISSING_FIELD;
        goto cleanup_subject;
    }

    /* copy comment. */
    comment = strdup(ctx->req.fieldmap[KEY_COMMENT]->val);
    if (NULL == comment)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto cleanup_subject;
    }

    /* filter comment. */
    retval = string_filter(comment);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_comment;
    }

    /* create the contact form. */
    retval = contact_form_create(&ctx->form, name, email, subject, comment);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_comment;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_comment;

cleanup_comment:
    free(comment);

cleanup_subject:
    free(subject);

cleanup_email:
    free(email);

cleanup_name:
    free(name);

done:
    return retval;
}
