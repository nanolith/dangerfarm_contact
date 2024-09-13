#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>

#include "../lmdb/lmdb_internal.h"
#include "../../../src/contactdb/contactdb_connection.h"

int nondet_retval();
uint64_t nondet_key();

DANGERFARM_CONTACT_IMPORT_contact_form;

int contactdb_connection_form_get_next(
    MDB_cursor* cursor, MDB_val* key, MDB_val* val, bool* found,
    uint64_t* p_key)
{
    contact_form* form;

    MODEL_ASSERT(prop_MDB_cursor_valid(cursor));
    MODEL_ASSERT(NULL != key);
    MODEL_ASSERT(NULL != key->mv_data);
    MODEL_ASSERT(sizeof(uint64_t) == key->mv_size);
    MODEL_ASSERT(NULL != val);
    MODEL_ASSERT(NULL != found);

    int retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        retval = contact_form_create(&form, "na", "em", "so", "co");
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        if (cursor->count > 0)
        {
            --(cursor->count);

            /* set the key. */
            key->mv_data = p_key;
            key->mv_size = (NULL == p_key) ? 0 :sizeof(*p_key);

            /* set the data. */
            val->mv_data = form;
            val->mv_size = contact_form_compute_size(form);

            if (NULL != p_key)
            {
                *p_key = nondet_key();
            }

            if (NULL != cursor->txn->temp_object)
            {
                free(cursor->txn->temp_object);
            }
            cursor->txn->temp_object = form;

            *found = true;
            return STATUS_SUCCESS;
        }
        else
        {
            free(form);
            *found = false;
            return STATUS_SUCCESS;
        }
    }
    else
    {
        switch (retval)
        {
            case ERROR_DATABASE_CURSOR_GET:
            case ERROR_CONTACTDB_GET_INVALID_SIZE:
                return retval;

            default:
                return ERROR_DATABASE_CURSOR_GET;
        }
    }
}
