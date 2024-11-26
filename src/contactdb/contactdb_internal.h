#pragma once

#include <dangerfarm_contact/cbmc/function_contracts.h>
#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/function_decl.h>
#include <dangerfarm_contact/status_codes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DATABASE_CAPABILITY_CONTACT_FORM_APPEND                 0x0001
#define DATABASE_CAPABILITY_CONTACT_FORM_GET                    0x0002
#define DATABASE_CAPABILITY_CONTACT_FORM_DELETE                 0x0004
#define DATABASE_CAPABILITY_CONTACT_FORM_COUNT_GET              0x0008
#define DATABASE_CAPABILITY_CONTACT_FORM_LIST_GET               0x0010
#define DATABASE_CAPABILITY_TRUNCATE                            0x0020

#define DATABASE_ROLE_WEB_APPLICATION \
    (DATABASE_CAPABILITY_CONTACT_FORM_APPEND)

#define DATABASE_ROLE_ADMIN_TOOL \
    (   DATABASE_CAPABILITY_CONTACT_FORM_APPEND \
      | DATABASE_CAPABILITY_CONTACT_FORM_GET \
      | DATABASE_CAPABILITY_CONTACT_FORM_DELETE \
      | DATABASE_CAPABILITY_CONTACT_FORM_COUNT_GET \
      | DATABASE_CAPABILITY_CONTACT_FORM_LIST_GET \
      | DATABASE_CAPABILITY_TRUNCATE)

typedef struct contactdb_connection contactdb_connection;

typedef struct contactdb_context contactdb_context;
struct contactdb_context
{
    char* db_path;
    char* socket_path;
    int sock;
    bool listen_socket;
    uint64_t root_capabilities;
    contactdb_connection* conn;
    bool should_terminate;
};

/**
 * \brief Return true if the given \ref contactdb_context is valid.
 *
 * \param ctx           The context to verify.
 *
 * \returns true if this context is valid, and false otherwise.
 */
bool prop_is_valid_contactdb_context(const contactdb_context* ctx);

/**
 * \brief Given an argument count and vector, create a contactdb context.
 *
 * \param ctx           Pointer to the context pointer to be populated with the
 *                      context on success.
 * \param argc          The argument count.
 * \param argv          The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_context_create_from_arguments(
    contactdb_context** ctx, int argc, char* argv[]);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactdb_context_create_from_arguments,
    contactdb_context** ctx, int argc, char* argv[])
        /* ctx variable must be accessible. */
        MODEL_CHECK_OBJECT_RW(ctx, sizeof(*ctx));
        /* argc must be >= 0. */
        MODEL_ASSERT(argc >= 0);
        /* argv must be accessible. */
        MODEL_CHECK_OBJECT_READ(argv, argc * sizeof(char*));
MODEL_CONTRACT_PRECONDITIONS_END(contactdb_context_create_from_arguments)

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    contactdb_context_create_from_arguments,
    int retval, contactdb_context** ctx)
        /* on success... */
        if (STATUS_SUCCESS == retval)
        {
            /* the context is valid. */
            MODEL_ASSERT(prop_is_valid_contactdb_context(*ctx));
        }
        /* on failure... */
        else
        {
            /* the context is set to NULL. */
            MODEL_ASSERT(NULL == *ctx);
        }
MODEL_CONTRACT_POSTCONDITIONS_END(contactdb_context_create_from_arguments)

/**
 * \brief Release a contactdb context.
 *
 * \param ctx           The context to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_context_release(contactdb_context* ctx);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactdb_context_release, contactdb_context* ctx)
        /* the context is valid. */
        MODEL_ASSERT(prop_is_valid_contactdb_context(ctx));
MODEL_CONTRACT_PRECONDITIONS_END(contactdb_context_release)

/* postconditions. */
MODEL_CONTRACT_POSTCONDITIONS_BEGIN(
    contactdb_context_release, int retval)
MODEL_CONTRACT_POSTCONDITIONS_END(contactdb_context_release)

/**
 * \brief Confirm whether the given capability exists in this context.
 *
 * \param ctx           The context to check.
 * \param cap           The capability to check against.
 *
 * \returns true if the contactdb has this capability, and false otherwise.
 */
bool contactdb_has_capability(const contactdb_context* ctx, const uint64_t cap);

/**
 * \brief Daemonize the contactdb service.
 *
 * \param ctx           The context to use for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_daemonize(contactdb_context* ctx);

/**
 * \brief Disable the signal handler.
 *
 * \param ctx           The context to use for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_disable_signal_handler(contactdb_context* ctx);

/**
 * \brief Drop privileges to only those needed for database communication.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_drop_privileges(contactdb_context* ctx);

/**
 * \brief Install a signal handler.
 *
 * \param ctx           The context to use for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_install_signal_handler(contactdb_context* ctx);

/**
 * \brief Accept and dispatch a connection.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on a FATAL error.
 */
int FN_DECL_MUST_CHECK
contactdb_accept_and_dispatch(contactdb_context* ctx);

/**
 * \brief Decode and dispatch a contactdb request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int FN_DECL_MUST_CHECK
contactdb_decode_and_dispatch(contactdb_context* ctx, int sock);

/**
 * \brief Decode and dispatch a contactdb contact form append request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int FN_DECL_MUST_CHECK
contactdb_dnd_contact_form_append(contactdb_context* ctx, int sock);

/**
 * \brief Decode and dispatch a contactdb contact form get count request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int FN_DECL_MUST_CHECK
contactdb_dnd_contact_form_get_count(contactdb_context* ctx, int sock);

/**
 * \brief Decode and dispatch a contactdb contact form get list request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int FN_DECL_MUST_CHECK
contactdb_dnd_contact_form_get_list(contactdb_context* ctx, int sock);

/**
 * \brief Decode and dispatch a contactdb contact form get request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int FN_DECL_MUST_CHECK
contactdb_dnd_contact_form_get(contactdb_context* ctx, int sock);

/**
 * \brief Decode and dispatch a contactdb contact form delete request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int FN_DECL_MUST_CHECK
contactdb_dnd_contact_form_delete(contactdb_context* ctx, int sock);
