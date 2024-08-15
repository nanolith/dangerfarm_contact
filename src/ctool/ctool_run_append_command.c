#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <stdio.h>

#include "ctool_internal.h"

DANGERFARM_CONTACT_IMPORT_contact_form;
DANGERFARM_CONTACT_IMPORT_protocol_database;

/**
 * \brief Run an append command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_append_command(ctool_context* ctx)
{
    int retval, release_retval;
    contact_form* form = NULL;
    uint32_t status = STATUS_SUCCESS;

    /* create a contact form using the parameters. */
    retval =
        contact_form_create(
            &form, ctx->contact_form_name, ctx->contact_form_email,
            ctx->contact_form_subject, ctx->contact_form_comment);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error creating a contact form instance.\n");
        goto done;
    }

    /* send the contact form append request to the socket. */
    retval = database_write_contact_form_append_request(ctx->sock, form);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error sending the contact form to the database.\n");
        goto cleanup_form;
    }

    /* read the response for this command. */
    retval = database_read_contact_form_append_response(&status, ctx->sock);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error reading response from the database.\n");
        goto cleanup_form;
    }

    /* did the request fail? */
    if (STATUS_SUCCESS != status)
    {
        const char* error = status_decode(status);
        fprintf(stderr, "Append contact failed: %s.\n", error);
        retval = (int)status;
        goto cleanup_form;
    }

    printf("Contact appended successfully.\n");

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_form;

cleanup_form:
    release_retval = contact_form_release(form);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
