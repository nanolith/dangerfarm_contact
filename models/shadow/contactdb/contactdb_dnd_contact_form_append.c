#include <dangerfarm_contact/cbmc/model_assert.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../../../src/contactdb/contactdb_internal.h"
#include "../libcontact/status_code_shadow.h"
#include "../unix/unix_shadow.h"

int contactdb_dnd_contact_form_append(contactdb_context* ctx, int sock)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_dnd_contact_form_append, ctx, sock);

    int retval = random_status_code();

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_dnd_contact_form_append, retval);

    return retval;
}
