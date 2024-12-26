#include <dangerfarm_contact/cbmc/model_assert.h>
#include <unistd.h>

int close(int fd)
{
    MODEL_ASSERT(fd >= 0);

    return 0;
}
