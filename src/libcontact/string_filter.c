#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdbool.h>

static void blank_and_advance(char** str, size_t length);
static bool is_lower_control_character(const char* str);

/**
 * \brief Filter a string, replacing any invalid UTF-8 sequences or HTML /
 * commandline unsafe sequences with spaces.
 *
 * \param str           The string to filter.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int string_filter(char* str)
{
    while (0 != *str)
    {
        if (is_lower_control_character(str))
        {
            blank_and_advance(&str, 1);
        }
        else
        {
            ++str;
        }
    }

    return STATUS_SUCCESS;
}

/**
 * \brief Check to see if the character at the start of the string is a lower
 * control character.
 *
 * \param str           The string to check.
 *
 * \returns true if this is a lower control character and false otherwise.
 */
static bool is_lower_control_character(const char* str)
{
    if ((*str > 0x00 && *str <= 0x1F) || *str == 0x7F)
    {
        return true;
    }

    return false;
}

/**
 * Blank the given number of characters and advance the pointer.
 *
 * \param str           The string pointer pointer to modify.
 */
static void blank_and_advance(char** str, size_t length)
{
    while (length--)
    {
        if (0 != **str)
        {
            **str = ' ';
        }

        ++(*str);
    }
}
