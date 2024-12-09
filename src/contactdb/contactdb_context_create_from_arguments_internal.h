#pragma once

#include <dangerfarm_contact/function_decl.h>

#include "contactdb_internal.h"

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
int FN_DECL_MUST_CHECK
contactdb_context_create_from_arguments_set_string(
    char** str, const char* opt, const char* value);

/* preconditions. */
MODEL_CONTRACT_PRECONDITIONS_BEGIN(
    contactdb_context_create_from_arguments_set_string, char** str,
    const char* opt, const char* value)
        /* str is accessible. */
        MODEL_CHECK_OBJECT_RW(str, sizeof(*str));
        /* opt is not NULL. */
        MODEL_ASSERT(NULL != opt);
        /* value is not NULL. */
        MODEL_ASSERT(NULL != value);
MODEL_CONTRACT_PRECONDITIONS_END(
    contactdb_context_create_from_arguments_set_string)

/**
 * \brief Read arguments, populating the context.
 *
 * \brief ctx           The context to populate with arguments.
 * \brief argc          The argument count.
 * \brief argv          The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_context_create_from_arguments_read_args(
    contactdb_context* ctx, int argc, char* argv[]);

/**
 * \brief Bind the local domain socket for this context.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int FN_DECL_MUST_CHECK
contactdb_context_create_from_arguments_bind_local_socket(
    contactdb_context* ctx);
