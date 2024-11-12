#include <dangerfarm_contact/protocol/database.h>
#include <dangerfarm_contact/status_codes.h>

int nondet_retval();

int DANGERFARM_CONTACT_SYM(database_write_contact_form_list_response)(
    int s, const uint32_t status, const uint64_t count,
    const uint64_t* id_list)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_list_response), s,
        status, count, id_list);

    int retval = nondet_retval();
    if (STATUS_SUCCESS != retval)
    {
        retval = ERROR_SOCKET_WRITE;
    }

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        DANGERFARM_CONTACT_SYM(database_write_contact_form_list_response),
        retval);

    return retval;
}
