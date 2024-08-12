#include <dangerfarm_contact/status_codes.h>
#include <stdio.h>
#include <string.h>

#include "contactdb_context_create_from_arguments_internal.h"

/**
 * \brief Set the given string argument, returning an error if the string
 * argument was already set.
 *
 * \param str           The string argument to set.
 * \param opt           The option being set (for error logging).
 * \param value         The value to which this argument is set.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactdb_context_create_from_arguments_set_string(
    char** str, const char* opt, const char* value)
{
    /* check for dupe. */
    if (NULL != *str)
    {
        fprintf(stderr, "%s parameter used twice!\n", opt);
        return ERROR_CONTACTDB_BAD_PARAMETER;
    }

    /* set the socket path. */
    *str = strdup(value);
    if (NULL == *str)
    {
        fprintf(stderr, "out of memory.\n");
        return ERROR_GENERAL_OUT_OF_MEMORY;
    }

    /* success. */
    return STATUS_SUCCESS;
}
