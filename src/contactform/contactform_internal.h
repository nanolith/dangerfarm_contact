#pragma once

#include <dangerfarm_contact/data/contact_form.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <kcgi.h>

enum contactform_drop_privileges_step
{
    DROP_PRIV_STEP_KCGI_PARSE = 1,
    DROP_PRIV_STEP_COMPLETE   = 2,
};

enum contactform_request_type
{
    CONTACTFORM_REQUEST_TYPE_OPTIONS = 1,
    CONTACTFORM_REQUEST_TYPE_POST = 2,
    CONTACTFORM_REQUEST_TYPE_INVALID = 3
};

typedef struct contactform_context contactform_context;
struct contactform_context
{
    int dbsock;
    pid_t dbpid;
    contact_form* form;
    bool kreq_initialized;
    struct kreq req;
    int request_type;
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
 * \brief Parse the CGI content, creating a contact form to send to the helper.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int contactform_context_read_cgi(contactform_context* ctx);

/**
 * \brief Clean up context data before calling into the CGI parse child. This
 * function ensures, for instance, that when parsing untrusted network data, an
 * exploit has no access to the database socket.
 *
 * \param ctx           The cloned context for this operation.
 */
void contactform_context_child_cleanup(contactform_context* ctx);

/**
 * \brief Decode the method type into a contact form request type.
 *
 * \param method        The KCGI HTTP request method to decode.
 *
 * \returns the request type to perform.
 */
int contactform_context_decode_request_type(int method);

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
