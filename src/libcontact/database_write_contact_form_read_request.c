#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

/**
 * \brief Write a contact read request to the socket.
 *
 * \param s         The socket to which this request is written.
 * \param id        The id of the contact form to be read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_write_contact_form_read_request(int s, uint64_t id)
{
    int retval;

    /* write the request id. */
    retval = socket_write_uint32(s, DATABASE_REQUEST_ID_CONTACT_FORM_GET);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* write the contact form id. */
    retval = socket_write_uint64(s, id);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
