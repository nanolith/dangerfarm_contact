#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctool_internal.h"

/**
 * \brief Run a list command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_list_command(ctool_context* ctx)
{
    int retval;
    uint32_t status = STATUS_SUCCESS;
    uint64_t count = 0;
    uint64_t* list = NULL;

    /* write a list request to the socket. */
    retval = database_write_contact_form_list_request(ctx->sock);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error attempting to write a list request.\n");
        goto done;
    }

    /* read the response for this command. */
    retval =
        database_read_contact_form_list_response(
            &status, &count, &list, ctx->sock);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error attempting to read a list response.\n");
        goto done;
    }

    /* did the request fail? */
    if (STATUS_SUCCESS != status)
    {
        const char* error = status_decode(status);
        fprintf(stderr, "List failed: %s.\n", error);
        retval = (int)status;
        goto done;
    }

    /* list the entries. */
    printf("Number of entries: %lu.\n", count);
    for (uint64_t i = 0; i < count; ++i)
    {
        printf("  %lu\n", list[i]);
    }
    printf("\n\n");

    /* clear and free the list. */
    memset(list, 0, count * sizeof(uint64_t));
    free(list);

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
