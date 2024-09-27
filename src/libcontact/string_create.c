#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/string.h>
#include <stdlib.h>

/**
 * \brief Create a string from a data pointer and size.
 *
 * \note Any null bytes in the data will be changed to ' ' to ensure that the
 * string can be fully read.
 *
 * \param str           Pointer to the character pointer for this string to set
 *                      on success.
 * \param data          Pointer to the data for this string.
 * \param size          The size of this data. The resulting string will be
 *                      size + 1 to account for the ASCII zero.
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(string_create)(
    char** str, const void* data, size_t size)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(string_create), str, data, size);

    int retval;
    char* tmp = NULL;
    const char* bdata = (const char*)data;

    /* attempt to allocate memory for this string. */
    tmp = (char*)malloc(size + 1);
    if (NULL == tmp)
    {
        *str = NULL;
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* copy over data, changing null bytes to spaces. */
    for (size_t i = 0; i < size; ++i)
    {
        tmp[i] = bdata[i] == 0 ? ' ' : bdata[i];
    }

    /* zero the last byte of this string. */
    tmp[size] = 0;

    /* Success. Set the string and return. */
    *str = tmp;
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(string_create), retval, str, size);

    return retval;
}
