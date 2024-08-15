#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/util/socket.h>

/**
 * \brief Read a database request id from the socket.
 *
 * \param req       The request to read.
 * \param s         The socket from which this request is read.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_read_request_id)(uint32_t* req, int s)
{
    return socket_read_uint32(req, s);
}
