#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Given an allocated string, clear and release it.
 *
 * \param str           The string to release.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(string_release)(char* str)
{
    size_t len = strlen(str);

    memset(str, 0, len);
    free(str);

    return STATUS_SUCCESS;
}
