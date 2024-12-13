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
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_context_create_from_arguments_set_string, str, opt, value);

    int retval;

    /* check for dupe. */
    if (NULL != *str)
    {
        MODEL_EXEMPT(fprintf(stderr, "%s parameter used twice!\n", opt));
        retval = ERROR_CONTACTDB_BAD_PARAMETER;
        goto done;
    }

    /* duplicate the string. */
    *str = strdup(value);
    if (NULL == *str)
    {
        MODEL_EXEMPT(fprintf(stderr, "out of memory.\n"));
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_context_create_from_arguments_set_string, retval, str);

    return retval;
}
