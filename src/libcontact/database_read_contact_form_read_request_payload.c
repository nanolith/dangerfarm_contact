#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>
#include <dangerfarm_contact/util/socket.h>

DANGERFARM_CONTACT_IMPORT_util_socket;

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
int DANGERFARM_CONTACT_SYM(database_read_contact_form_read_request_payload)(
    uint64_t* id, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_read_request_payload),
        id, s);

    /* read the id. */
    int retval = socket_read_uint64(id, s);
    if (STATUS_SUCCESS != retval)
    {
        *id = DATABASE_PROTOCOL_INVALID_ID;
        goto done;
    }

    /* if the id is invalid, that's an error. */
    if (DATABASE_PROTOCOL_INVALID_ID == *id)
    {
        retval = ERROR_DATABASE_PROTOCOL_INVALID_ID;
        goto done;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_read_request_payload),
        retval, id);

    return retval;
}
