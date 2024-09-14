#include <dangerfarm_contact/cbmc/model_assert.h>

#include "../../../src/contactdb/contactdb_internal.h"
#include "../libcontact/status_code_shadow.h"

/**
 * \brief Accept and dispatch a connection.
 *
 * \param ctx           The context for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - zero on success.
 *      - non-zero on a FATAL error.
 */
int contactdb_accept_and_dispatch(contactdb_context* ctx)
{
    MODEL_ASSERT(prop_is_valid_contactdb_context(ctx));

    /* trigger the end to the outer loop in main. */
    ctx->should_terminate = true;

    return random_status_code();
}
