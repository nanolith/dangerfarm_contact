#include <dangerfarm_contact/cbmc/model_assert.h>

#include "../../../src/contactdb/contactdb_connection.h"
#include "../lmdb/lmdb_internal.h"

/* stub version of this property. */
bool prop_is_valid_contactdb_connection(const contactdb_connection* conn)
{
    return true;
}
