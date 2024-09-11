#include <dangerfarm_contact/cbmc/model_assert.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../../../src/contactdb/contactdb_internal.h"
#include "../libcontact/status_code_shadow.h"
#include "../unix/unix_shadow.h"

int contactdb_dnd_contact_form_append(contactdb_context* ctx, int sock)
{
    MODEL_ASSERT(prop_is_valid_contactdb_context(ctx));
    MODEL_ASSERT(prop_is_open_fd(sock));

    return random_status_code();
}
