#pragma once

#include <dangerfarm_contact/cbmc/function_contracts.h>
#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/contracts/properties/unix.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/function_decl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <kcgi.h>

#define CONTACTDB_SOCKET        "/tmp/contactdb_app.sock"

enum contactform_drop_privileges_step
{
    DROP_PRIV_STEP_LIMIT_FS_ACCESS = 1,
    DROP_PRIV_STEP_KCGI_PARSE = 2,
    DROP_PRIV_STEP_COMPLETE   = 3,
};

enum contactform_request_type
{
    CONTACTFORM_REQUEST_TYPE_OPTIONS = 1,
    CONTACTFORM_REQUEST_TYPE_POST = 2,
    CONTACTFORM_REQUEST_TYPE_INVALID = 3
};

enum contactform_key
{
    KEY_NAME,
    KEY_EMAIL,
    KEY_SUBJECT,
    KEY_COMMENT,
    KEY_MAX
};

typedef struct contactform_context contactform_context;
struct contactform_context
{
    int dbsock;
    pid_t dbpid;
    DANGERFARM_CONTACT_SYM(contact_form)* form;
    bool kreq_initialized;
    struct kreq req;
    int request_type;
};

/**
 * \brief Verify that the given drop privileges step is valid.
 *
 * \param step          The step to verify.
 *
 * \returns true if this step is valid and false otherwise.
 */
bool prop_valid_drop_privileges_step(int step);

/**
 * \brief Verify that the given request type is valid.
 *
 * \param req           The request type to verify.
 *
 * \returns true if this request type is valid and false otherwise.
 */
bool prop_valid_request_type(int req);

/**
 * \brief Verify that the given contact form key is valid.
 *
 * \param key           The contact form key to verify.
 *
 * \returns true if this contact form key is valid and false otherwise.
 */
bool prop_valid_contactform_key(int key);

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
int FN_DECL_MUST_CHECK
contactform_context_create(contactform_context** ctx);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactform_context_create, contactform_context** ctx)
        /* ctx variable must be accessible. */
        MODEL_CHECK_OBJECT_RW(ctx, sizeof(*ctx));
MODEL_CONTRACT_PRECONDITIONS_END(contactform_context_create)

/**
 * \brief Release a \ref contactform_context instance.
 *
 * \param ctx           The context to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactform_context_release(contactform_context* ctx);

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
int FN_DECL_MUST_CHECK
contactform_database_helper_create(int* s, pid_t* pid);

/**
 * \brief Parse the CGI content, creating a contact form to send to the helper.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactform_context_read_cgi(contactform_context* ctx);

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
 * \brief Decode a contact form instance using form data.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactform_form_decode(contactform_context* ctx);

/**
 * \brief Perform a CGI request action.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactform_perform_cgi_request(contactform_context* ctx);

/**
 * \brief Perform a drop privileges step.
 *
 * \param step          The step to perform.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactform_drop_privileges(int step);
