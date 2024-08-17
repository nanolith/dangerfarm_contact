#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <inttypes.h>
#include <stdio.h>

#include "ctool_internal.h"

DANGERFARM_CONTACT_IMPORT_protocol_database;

/**
 * \brief Run a delete command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_delete_command(ctool_context* ctx)
{
    int retval;
    uint32_t status = STATUS_SUCCESS;

    /* write a delete request to the socket. */
    retval =
        database_write_contact_form_delete_request(ctx->sock, ctx->form_id);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error attempting to write a delete request.\n");
        goto done;
    }

    /* read the response for this command. */
    retval = database_read_contact_form_delete_response(&status, ctx->sock);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error attempting to read a get response.\n");
        goto done;
    }

    /* did the request fail? */
    if (STATUS_SUCCESS != status)
    {
        const char* error = status_decode(status);
        fprintf(stderr, "Delete failed: %s.\n", error);
        retval = (int)status;
        goto done;
    }

    /* Output status. */
    printf("Delete %" PRIu64 " succeeded.\n", ctx->form_id);

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
