#include "../../../src/contactdb/contactdb_connection.h"
#include "../lmdb/lmdb_internal.h"

/**
 * \brief Return true if the given \ref contactdb_connection is valid.
 *
 * \param conn          The connection to verify.
 *
 * \returns true if this connection is valid, and false otherwise.
 */
bool prop_is_valid_contactdb_connection(const contactdb_connection* conn)
{
    MODEL_ASSERT(prop_MDB_env_opened(conn->env));
    MODEL_ASSERT(conn->global_db >= 0);
    MODEL_ASSERT(conn->contact_db >= 0);

    return true;
}
