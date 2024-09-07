#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/status_codes.h>
#include <errno.h>
#include <stdlib.h>

#include "lmdb_internal.h"

void mdb_cursor_close(MDB_cursor* cursor)
{
    MODEL_ASSERT(prop_MDB_cursor_valid(cursor));

    if (NULL != cursor->key_buffer)
    {
        free(cursor->key_buffer);
    }

    free(cursor);
}
