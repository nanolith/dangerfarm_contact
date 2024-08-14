#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdio.h>

#include "ctool_internal.h"

DANGERFARM_CONTACT_IMPORT_contact_form;

/**
 * \brief Run a get command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_get_command(ctool_context* ctx)
{
    int retval, release_retval;
    uint32_t status = STATUS_SUCCESS;
    contact_form* form = NULL;
    char* name = NULL;
    char* email = NULL;
    char* subject = NULL;
    char* comment = NULL;

    /* write a get request to the socket. */
    retval = database_write_contact_form_read_request(ctx->sock, ctx->form_id);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error attempting to write a get request.\n");
        goto done;
    }

    /* read the response for this command. */
    retval =
        database_read_contact_form_read_response(&status, &form, ctx->sock);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error attempting to read a get response.\n");
        goto done;
    }

    /* did the request fail? */
    if (STATUS_SUCCESS != status)
    {
        const char* error = status_decode(status);
        fprintf(stderr, "Get failed: %s.\n", error);
        retval = (int)status;
        goto done;
    }

    /* extract name. */
    retval = contact_form_extract_name(&name, form);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_form;
    }

    /* extract email. */
    retval = contact_form_extract_email(&email, form);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_name;
    }

    /* extract subject. */
    retval = contact_form_extract_subject(&subject, form);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_email;
    }

    /* extract comment. */
    retval = contact_form_extract_comment(&comment, form);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_subject;
    }

    /* output contact. */
    printf("name:    %s\n", name);
    printf("email:   %s\n", email);
    printf("subject: %s\n", subject);
    printf("comment:\n\n%s\n\n", comment);

    /* success. */
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

cleanup_form:
    release_retval = contact_form_release(form);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
