#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

/**
 * \brief Read a contact read request payload from the socket.
 *
 * \param id        Pointer to receive the contact form id on success.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int database_read_contact_form_read_request_payload(uint64_t* id, int s)
{
    return socket_read_uint64(id, s);
}
