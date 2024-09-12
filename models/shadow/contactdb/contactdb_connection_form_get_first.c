#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>

#include "../lmdb/lmdb_internal.h"
#include "../../../src/contactdb/contactdb_connection.h"

int nondet_retval();
uint64_t nondet_key();

DANGERFARM_CONTACT_IMPORT_contact_form;

int contactdb_connection_form_get_first(
    MDB_cursor** cursor, contactdb_connection* conn, MDB_txn* txn, MDB_val* key,
    MDB_val* val, bool* found, uint64_t* p_key)
{
    contact_form* form;

    MODEL_ASSERT(NULL != cursor);
    MODEL_ASSERT(prop_is_valid_contactdb_connection(conn));
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    MODEL_ASSERT(NULL != key);
    MODEL_ASSERT(NULL != val);
    MODEL_ASSERT(NULL != found);

    int retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        retval = contact_form_create(&form, "na", "em", "su", "co");
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        retval = mdb_cursor_open(txn, conn->contact_db, cursor);
        if (STATUS_SUCCESS != retval)
        {
            free(form);
            return ERROR_DATABASE_CURSOR_OPEN;
        }

        if ((*cursor)->count > 0)
        {
            --((*cursor)->count);

            MODEL_ASSERT(prop_valid_contact_form(form));

            /* set the key. */
            key->mv_data = p_key;
            key->mv_size = sizeof(*p_key);

            /* set the data. */
            val->mv_data = form;
            val->mv_size = contact_form_compute_size(form);

            if (NULL != p_key)
            {
                *p_key = nondet_key();
            }

            if (NULL != txn->temp_object)
            {
                free(txn->temp_object);
            }
            txn->temp_object = form;

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
            case ERROR_DATABASE_CURSOR_OPEN:
            case ERROR_DATABASE_CURSOR_GET:
            case ERROR_CONTACTDB_GET_INVALID_SIZE:
                return retval;

            default:
                return ERROR_DATABASE_CURSOR_GET;
        }
    }
}
