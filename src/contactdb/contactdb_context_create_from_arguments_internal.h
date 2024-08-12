#pragma once

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
    char** str, const char* opt, const char* value);
