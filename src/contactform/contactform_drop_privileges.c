#include <dangerfarm_contact/status_codes.h>
#include <unistd.h>

#ifdef __FreeBSD__
#include <sys/capsicum.h>
#endif

#include "contactform_internal.h"

/* forward decls. */
static int reduce_filesystem_access(void);
static int drop_privileges_for_parse(void);
static int drop_all_privileges(void);

/**
 * \brief Perform a drop privileges step.
 *
 * \param step          The step to perform.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_drop_privileges(int step)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(contactform_drop_privileges, step);

    int retval;

    switch (step)
    {
        case DROP_PRIV_STEP_LIMIT_FS_ACCESS:
            retval = reduce_filesystem_access();
            break;

        case DROP_PRIV_STEP_KCGI_PARSE:
            retval = drop_privileges_for_parse();
            break;

        case DROP_PRIV_STEP_COMPLETE:
            retval = drop_all_privileges();
            break;

        default:
            retval = ERROR_CONTACTFORM_INVALID_DROP_PRIVILEGES_STEP;
            break;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(contactform_drop_privileges, retval);

    return retval;
}

/**
 * \brief Reduce filesystem access prior to initialization.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int reduce_filesystem_access(void)
{
    int retval;

    (void)retval;

    #ifdef __OpenBSD__
    /* this process only accesses the contactdb application socket. */
    retval = unveil(CONTACTDB_SOCKET, "rw");
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CONTACTFORM_DROP_PRIVILEGES;
    }

    /* don't allow any other filesystem access. */
    retval = unveil(NULL, NULL);
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CONTACTFORM_DROP_PRIVILEGES;
    }
    #endif

    return STATUS_SUCCESS;
}

/**
 * \brief Drop privileges prior to the kcgi parse step.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int drop_privileges_for_parse(void)
{
    int retval;

    (void)retval;

    #ifdef __OpenBSD__
    retval = pledge("stdio proc", NULL);
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CONTACTFORM_DROP_PRIVILEGES;
    }
    #endif

    return STATUS_SUCCESS;
}

/**
 * \brief Drop all privileges prior to running the main CGI app.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
static int drop_all_privileges(void)
{
    int retval;

    (void)retval;

    #ifdef __FreeBSD__
    retval = cap_enter();
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CONTACTFORM_DROP_PRIVILEGES;
    }
    #endif

    #ifdef __OpenBSD__
    retval = pledge("stdio", NULL);
    if (STATUS_SUCCESS != retval)
    {
        return ERROR_CONTACTFORM_DROP_PRIVILEGES;
    }
    #endif

    return STATUS_SUCCESS;
}
