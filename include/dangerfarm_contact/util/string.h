#pragma once

/**
 * \brief Given an allocated string, clear and release it.
 *
 * \param str           The string to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int string_release(char* str);
