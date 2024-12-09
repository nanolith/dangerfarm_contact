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
    MODEL_CONTRACT_CHECK_PRECONDITIONS(
        contactdb_connection_form_get_next, cursor, key, val, found, p_key);

    int release_retval;
    contact_form* form;

    int retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        retval = contact_form_create(&form, "na", "em", "so", "co");
        if (STATUS_SUCCESS != retval)
        {
            goto fail;
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

                if (COUNTER_VALUE_INVALID == *p_key)
                {
                    retval = ERROR_CONTACTDB_BAD_COUNTER_VALUE;
                    goto cleanup_form;
                }
            }

            if (NULL != cursor->txn->temp_object)
            {
                free(cursor->txn->temp_object);
            }
            cursor->txn->temp_object = form;

            *found = true;
            retval = STATUS_SUCCESS;
            goto done;
        }
        else
        {
            *found = false;
            retval = STATUS_SUCCESS;
            goto cleanup_form;
        }
    }
    else
    {
        switch (retval)
        {
            case ERROR_DATABASE_CURSOR_GET:
            case ERROR_CONTACTDB_GET_INVALID_SIZE:
                goto fail;

            default:
                retval = ERROR_DATABASE_CURSOR_GET;
                goto fail;
        }
    }

cleanup_form:
    release_retval = contact_form_release(form);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

fail:
    *found = false;
    *p_key = COUNTER_VALUE_INVALID;
    key->mv_data = NULL; key->mv_size = 0;
    val->mv_data = NULL; val->mv_size = 0;

done:
    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        contactdb_connection_form_get_next, retval, cursor, key, val, found,
        p_key);

    return retval;
}
