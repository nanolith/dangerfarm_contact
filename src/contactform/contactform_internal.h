#pragma once

#include <dangerfarm_contact/data/contact_form.h>
#include <unistd.h>

enum contactform_drop_privileges_step
{
    DROP_PRIV_STEP_KCGI_PARSE = 1,
    DROP_PRIV_STEP_COMPLETE   = 2,
};

typedef struct contactform_context contactform_context;
struct contactform_context
{
    int dbsock;
    pid_t dbpid;
    contact_form* form;
};

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
int contactform_context_create(contactform_context** ctx);

/**
 * \brief Release a \ref contactform_context instance.
 *
 * \param ctx           The context to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_context_release(contactform_context* ctx);

/**
 * \brief Create a database helper connection.
 *
 * \param s             Pointer to the descriptor to be set to the socket to
 *                      set to the socket connection to the helper.
 * \param pid           Pointer to set to the process id of this helper.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_database_helper_create(int* s, pid_t* pid);

/**
 * \brief Perform a drop privileges step.
 *
 * \param step          The step to perform.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_drop_privileges(int step);
