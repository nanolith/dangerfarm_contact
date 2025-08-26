#include <dangerfarm_contact/cbmc/model_assert.h>

_Noreturn void contactform_database_helper_entry(int s)
{
    MODEL_ASSERT(prop_is_open_fd(s));

    close(s);

    exit(0);
}
