#include <dangerfarm_contact/cbmc/model_assert.h>

#include "../../../src/contactform/contactform_internal.h"

/**
 * \brief Verify that the given \ref contactform_context is valid.
 *
 * \param ctx           The context to verify.
 *
 * \returns true if this context is valid and false otherwise.
 */
bool prop_valid_contactform_context(const contactform_context* ctx)
{
    MODEL_CHECK_OBJECT_READ(ctx, sizeof(*ctx));
    MODEL_ASSERT(ctx->dbsock >= 0);
    MODEL_ASSERT(ctx->dbpid >= 0);

    return true;
}
