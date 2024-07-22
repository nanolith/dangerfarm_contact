#pragma once

#include <unistd.h>

enum contactform_drop_privileges_step
{
    DROP_PRIV_STEP_KCGI_PARSE = 1,
    DROP_PRIV_STEP_COMPLETE   = 2,
};

struct contactform_context
{
    int dbsock;
    pid_t dbpid;
};

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
