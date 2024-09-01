#include <dangerfarm_contact/cbmc/model_assert.h>

#include "../../../src/contactdb/contactdb_internal.h"
#include "../libcontact/status_code_shadow.h"
#include "../unix/unix_shadow.h"

/**
 * \brief Decode and dispatch a contactdb request.
 *
 * \param ctx           The context for this operation.
 * \param sock          The socket for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on error.
 */
int contactdb_decode_and_dispatch(contactdb_context* ctx, int sock)
{
    MODEL_ASSERT(prop_is_valid_contactdb_context(ctx));
    MODEL_ASSERT(prop_is_open_fd(sock));

    return random_status_code();
}
