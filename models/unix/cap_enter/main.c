#include <dangerfarm_contact/cbmc/model_assert.h>
#include <unistd.h>

int cap_enter(void);

int main(int argc, char* argv[])
{
    int retval;

    /* Enter capability mode. */
    retval = cap_enter();
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
