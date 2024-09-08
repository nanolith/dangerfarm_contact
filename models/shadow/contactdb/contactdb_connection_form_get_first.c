#include <dangerfarm_contact/cbmc/model_assert.h>
#include <dangerfarm_contact/data/contact_form.h>
#include <dangerfarm_contact/status_codes.h>

#include "../lmdb/lmdb_internal.h"
#include "../../../src/contactdb/contactdb_connection.h"

int nondet_retval();
uint64_t nondet_key();

DANGERFARM_CONTACT_IMPORT_contact_form;

static contact_form const_form = {
    .name_size = 2,
    .email_size = 2,
    .subject_size = 2,
    .comment_size = 2,
    .data = {
        'n', 'a',
        'e', 'm', 
        's', 'u',
        'c', 'o' } };

int contactdb_connection_form_get_first(
    MDB_cursor** cursor, contactdb_connection* conn, MDB_txn* txn, MDB_val* key,
    MDB_val* val, bool* found, uint64_t* p_key)
{
    MODEL_ASSERT(NULL != cursor);
    MODEL_ASSERT(prop_is_valid_contactdb_connection(conn));
    MODEL_ASSERT(prop_MDB_txn_valid(txn));
    MODEL_ASSERT(NULL != key);
    MODEL_ASSERT(NULL != key->mv_data);
    MODEL_ASSERT(sizeof(uint64_t) == key->mv_size);
    MODEL_ASSERT(NULL != val);
    MODEL_ASSERT(NULL != found);

    int retval = nondet_retval();
    if (STATUS_SUCCESS == retval)
    {
        retval = mdb_cursor_open(txn, conn->contact_db, cursor);
        if (STATUS_SUCCESS != retval)
        {
            return ERROR_DATABASE_CURSOR_OPEN;
        }

        if ((*cursor)->count > 0)
        {
            --((*cursor)->count);

            /* set the data. */
            val->mv_data = &const_form;
            val->mv_size = sizeof(const_form);

            if (NULL != p_key)
            {
                *p_key = nondet_key();
            }

            *found = true;
            return STATUS_SUCCESS;
        }
        else
        {
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
