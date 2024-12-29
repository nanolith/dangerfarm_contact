#include <dangerfarm_contact/cbmc/model_assert.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t sid;
    int retval;

    /* create a new session and get the session id. */
    sid = setsid();
    if (sid < 0)
    {
        /* error */
        retval = 1;
        goto done;
    }

    /* the session id is greater than 0 if valid. */
    MODEL_ASSERT(sid > 0);

    /* success. */
    retval = 0;
    goto done;

done:
    return retval;
}
