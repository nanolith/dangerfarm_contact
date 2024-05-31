#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * \brief Read a list contact forms response from the socket.
 *
 * \param status    Pointer to receive the status code on success.
 * \param count     Pointer to receive the count of items to be read.
 * \param id_list   Pointer to receive the array of contact IDs.
 * \param s         The socket from which this response is read.
 *
 * \note id_list is updated with a dynamically allocated array which is owned
 * by the caller on success.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_read_contact_form_list_response(
    uint32_t* status, uint64_t* count, uint64_t** id_list, int s)
{
    int retval;
    ssize_t read_bytes;
    uint32_t request_id;
    uint64_t* tmp;

    /* read the request id. */
    retval = socket_read_uint32(&request_id, s);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* verify the request id. */
    if (DATABASE_REQUEST_ID_CONTACT_FORM_GET_LIST != request_id)
    {
        retval = ERROR_DATABASE_PROTOCOL_UNEXPECTED_REQUEST_ID;
        goto done;
    }

    /* read the status. */
    retval = socket_read_uint32(status, s);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* verify that the status was successful before decoding the payload. */
    if (STATUS_SUCCESS != *status)
    {
        retval = STATUS_SUCCESS;
        goto done;
    }

    /* read the count. */
    retval = socket_read_uint64(count, s);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* verify that the count is sane. */
    if (*count > DATABASE_PROTOCOL_MAX_COUNT)
    {
        retval = ERROR_DATABASE_PROTOCOL_INVALID_COUNT;
        goto done;
    }

    /* allocate memory for the id list. */
    size_t tmp_size = (*count) * sizeof(uint64_t);
    tmp = malloc(tmp_size);
    if (NULL == tmp)
    {
        retval = ERROR_GENERAL_OUT_OF_MEMORY;
        goto done;
    }

    /* clear memory. */
    memset(tmp, 0, tmp_size);

    /* attempt to read the list from the socket. */
    read_bytes = read(s, tmp, tmp_size);
    if (read_bytes < 0 || (size_t)read_bytes != tmp_size)
    {
        retval = ERROR_SOCKET_READ;
        goto cleanup_tmp;
    }

    /* success. */
    *id_list = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    memset(tmp, 0, tmp_size);
    free(tmp);

done:
    return retval;
}
