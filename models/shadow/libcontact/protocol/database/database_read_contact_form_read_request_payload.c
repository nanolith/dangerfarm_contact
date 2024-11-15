#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();
uint64_t nondet_id();

int DANGERFARM_CONTACT_SYM(database_read_contact_form_read_request_payload)(
    uint64_t* id, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_contact_form_read_request_payload),
        id, s);

    /* does this fail? */
    int retval = nondet_retval();
    if (STATUS_SUCCESS != retval)
    {
        *id = DATABASE_PROTOCOL_INVALID_ID;
        goto done;
    }

    /* generate an id. */
    *id = nondet_id();
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
