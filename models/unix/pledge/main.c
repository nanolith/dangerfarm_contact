#include <dangerfarm_contact/cbmc/model_assert.h>
#include <unistd.h>

int pledge(const char *promises, const char *execpromises);

int main(int argc, char* argv[])
{
    int retval;

    /* Pledge to remove syscall access. */
    retval = pledge("stdio", "stdio");
    if (retval < 0)
    {
        retval = 1;
        goto done;
    }

    /* success. */
    retval = 0;
    goto done;

done:
    return retval;
}
