#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(database_write_contact_form_read_request)(
    int s, uint64_t id)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_read_request),
        s, id);

    int retval = nondet_retval();
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_SOCKET_WRITE;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_read_request),
        retval);

    return retval;
}
