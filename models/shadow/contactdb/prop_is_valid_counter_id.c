#include "../../src/contactdb/contactdb_connection.h"

bool prop_is_valid_counter_id(uint64_t counter_id)
{
    switch (counter_id)
    {
        case COUNTER_ID_CONTACT_COUNT:
        case COUNTER_ID_CONTACT_KEY:
            return true;

        default:
            return false;
    }
}
