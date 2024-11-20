#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

/**
 * \brief Write a database truncate request to the socket.
 *
 * \param s         The socket to which this request is written.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on failure.
 */
int DANGERFARM_CONTACT_SYM(database_write_database_truncate_request)(int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_database_truncate_request), s);

    /* write the request id. */
    int retval = socket_write_uint32(s, DATABASE_REQUEST_ID_TRUNCATE);

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_database_truncate_request),
        retval);

    return retval;
}
