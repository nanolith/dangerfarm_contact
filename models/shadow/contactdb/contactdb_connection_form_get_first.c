#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>
#include <stdlib.h>

#include "../lmdb/lmdb_internal.h"
#include "../../../src/contactdb/contactdb_connection.h"

int nondet_retval();
uint64_t nondet_key();

uint64_t choose_key()
{
    uint64_t retval = nondet_key();

    MODEL_ASSUME(COUNTER_VALUE_INVALID != retval);

    return retval;
}

DANGERFARM_CONTACT_IMPORT_contact_form;

int contactdb_connection_form_get_first(
    MDB_cursor** cursor, contactdb_connection* conn, MDB_txn* txn, MDB_val* key,
    MDB_val* val, bool* found, uint64_t* p_key)
{
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_get_first, cursor, conn, txn, key, val, found,
        p_key);

    *cursor = NULL;

    contact_form* form;

    int retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        retval = contact_form_create(&form, "na", "em", "su", "co");
        if (STATUS_SUCCESS != retval)
        {
            goto fail;
        }

        retval = mdb_cursor_open(txn, conn->contact_db, cursor);
        if (STATUS_SUCCESS != retval)
        {
            free(form);
            *cursor = NULL;
            retval = ERROR_DATABASE_CURSOR_OPEN;
            goto fail;
        }

        if ((*cursor)->count > 0)
        {
            --((*cursor)->count);

            MODEL_ASSERT(prop_valid_contact_form(form));

            /* set the key. */
            key->mv_data = p_key;
            key->mv_size = (NULL == p_key) ? 0 :sizeof(*p_key);

            /* set the data. */
            val->mv_data = form;
            val->mv_size = contact_form_compute_size(form);

            if (NULL != p_key)
            {
                *p_key = choose_key();
            }

            if (NULL != txn->temp_object)
            {
                free(txn->temp_object);
            }
            txn->temp_object = form;

            *found = true;
            retval = STATUS_SUCCESS;
            goto done;
        }
        else
        {
            free(form);
            *found = false;
            retval = STATUS_SUCCESS;
            goto fail;
        }
    }
    else
    {
        switch (retval)
        {
            case ERROR_DATABASE_CURSOR_OPEN:
            case ERROR_DATABASE_CURSOR_GET:
            case ERROR_CONTACTDB_GET_INVALID_SIZE:
                goto fail;

            default:
                retval = ERROR_DATABASE_CURSOR_GET;
                goto fail;
        }
    }

fail:
    *found = false;
    *p_key = COUNTER_VALUE_INVALID;
    key->mv_data = NULL; key->mv_size = 0;
    val->mv_data = NULL; val->mv_size = 0;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_form_get_first, retval, cursor, key, val, found,
        p_key);

    return retval;
}
