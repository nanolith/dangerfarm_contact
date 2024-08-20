#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Write a list contact forms request to the socket.
 *
 * \param s         The socket to which this request is written.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_contact_form_list_request)(int s)
{
    return socket_write_uint32(s, DATABASE_REQUEST_ID_CONTACT_FORM_GET_LIST);
}
