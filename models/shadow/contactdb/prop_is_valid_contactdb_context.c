#include "../../../src/contactdb/contactdb_internal.h"
#include "../../../src/contactdb/contactdb_connection.h"

/**
 * \brief Return true if the given \ref contactdb_context is valid.
 *
 * \param ctx           The context to verify.
 *
 * \returns true if this context is valid, and false otherwise.
 */
bool prop_is_valid_contactdb_context(const contactdb_context* ctx)
{
    /* the db_path should be set. */
    MODEL_ASSERT(NULL != ctx->db_path);

    /* the socket_path should be set. */
    MODEL_ASSERT(NULL != ctx->socket_path);

    /* the socket should be a valid Unix socket. */
    MODEL_ASSERT(prop_is_valid_unix_desc(ctx->sock));

    /* the database connection should be valid. */
    MODEL_ASSERT(prop_is_valid_contactdb_connection(ctx->conn));

    return true;
}
