#include <dangerfarm_contact/protocol/database.h>

int nondet_retval();
uint32_t nondet_req();

int DANGERFARM_CONTACT_SYM(database_read_request_id)(uint32_t* req, int s)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_request_id), req, s);

    int retval = STATUS_SUCCESS;

    if (STATUS_SUCCESS != nondet_retval())
    {
        retval = ERROR_SOCKET_READ;
        *req = DATABASE_REQUEST_ID_INVALID;
    }
    else
    {
        *req = nondet_req();
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_read_request_id), retval, req);

    return retval;
}
