#pragma once

#include <stdbool.h>
#include <stdint.h>

enum ctool_command
{
    CTOOL_COMMAND_NONE                                          = 0,
    CTOOL_COMMAND_APPEND                                        = 1,
    CTOOL_COMMAND_GET_COUNT                                     = 2,
    CTOOL_COMMAND_LIST                                          = 3,
    CTOOL_COMMAND_GET                                           = 4,
    CTOOL_COMMAND_DELETE                                        = 5,
};

typedef struct ctool_context ctool_context;
struct ctool_context
{
    char* socket_path;
    int sock;
    uint64_t form_id;
    bool form_id_set;
    char* contact_form_name;
    char* contact_form_email;
    char* contact_form_subject;
    char* contact_form_comment;
    int command;
};

/**
 * \brief Given an argument count and vector, create a ctool context.
 *
 * \param ctx               Pointer to the context pointer to be populated with
 *                          the context on success.
 * \param argc              The argument count.
 * \param argv              The argument vector.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_context_create_from_arguments(
    ctool_context** ctx, int argc, char* argv[]);

/**
 * \brief Release a ctool context.
 *
 * \param ctx           The context to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_context_release(ctool_context* ctx);

/**
 * \brief Run a ctool command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_command(ctool_context* ctx);

/**
 * \brief Run an append command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_append_command(ctool_context* ctx);

/**
 * \brief Run a get count command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_get_count_command(ctool_context* ctx);

/**
 * \brief Run a list command.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int ctool_run_list_command(ctool_context* ctx);
