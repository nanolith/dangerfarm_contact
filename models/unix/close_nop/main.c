#include <dangerfarm_contact/cbmc/model_assert.h>
#include <unistd.h>

int nondet_descriptor();

int choose_descriptor()
{
    int retval = nondet_descriptor();

    MODEL_ASSUME(retval >= 0);

    return retval;
}

int main(int argc, char* argv[])
{
    int retval;

    /* Close a dummy descriptor. */
    retval = close(choose_descriptor());

    /* close_nop always succeeds. */
    MODEL_ASSERT(0 == retval);

    return retval;
}
