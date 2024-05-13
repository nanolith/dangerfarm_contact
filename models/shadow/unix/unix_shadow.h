#include <stdbool.h>

typedef struct fds __fds;

struct fds
{
    char* desc;
};

#define SHADOW_FD_COUNT 5

__fds __fd_shadow_list[SHADOW_FD_COUNT];

void unix_shadow_init();
bool prop_is_open_fd();
