#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "contactform_internal.h"

/**
 * \brief Create a \ref contactform_context instance.
 *
 * \param ctx           Pointer to the pointer to receive the context on
 *                      success.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_context_create(contactform_context** ctx)
{
    int retval, release_retval;
    contactform_context* tmp;

    /* allocate memory for this instance. */
    tmp = (contactform_context*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* clear memory. */
    memset(tmp, 0, sizeof(*tmp));
    tmp->dbsock = -1;
    tmp->dbpid = -1;

    /* create the helper instance. */
    retval = contactform_database_helper_create(&tmp->dbsock, &tmp->dbpid);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* success. */
    *ctx = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    release_retval = contactform_context_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
