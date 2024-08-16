#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <inttypes.h>
#include <stdio.h>

#include "ctool_internal.h"

DANGERFARM_CONTACT_IMPORT_protocol_database;

/**
 * \brief Run a get count command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_get_count_command(ctool_context* ctx)
{
    int retval;
    uint32_t status = STATUS_SUCCESS;
    uint64_t count = 0;

    /* write a get count request to the socket. */
    retval = database_write_contact_form_get_count_request(ctx->sock);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error attempting to write a get count request.\n");
        goto done;
    }

    /* read the response for this command. */
    retval =
        database_read_contact_form_get_count_response(
            &status, &count, ctx->sock);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error attempting to read a get count response.\n");
        goto done;
    }

    /* did the request fail? */
    if (STATUS_SUCCESS != status)
    {
        const char* error = status_decode(status);
        fprintf(stderr, "Get count failed: %s.\n", error);
        retval = (int)status;
        goto done;
    }

    printf("Contact form count: %" PRIu64 ".\n", count);

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
