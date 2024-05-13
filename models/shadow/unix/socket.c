#include <dangerfarm_contact/cbmc/model_assert.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "unix_shadow.h"

int nondet_int();

int socket(int domain, int type, int protocol)
{
    /* these are the only options we support. */
    MODEL_ASSERT(AF_UNIX == domain);
    MODEL_ASSERT(SOCK_STREAM == type);
    MODEL_ASSERT(0 == protocol);

    /* determine our behavior. */
    if (0 == nondet_int())
    {
        /* allocate a socket in the fds, if possible. */
        for (int i = 0; i < SHADOW_FD_COUNT; ++i)
        {
            if (NULL == __fd_shadow_list[i].desc)
            {
                __fd_shadow_list[i].desc = (char*)malloc(1);
                if (NULL == __fd_shadow_list[i].desc)
                {
                    errno = ENOMEM;
                    return -1;
                }

                return i;
            }

            errno = EMFILE;
            return -1;
        }
    }
    else
    {
        errno = EPERM;
        return -1;
    }
}
