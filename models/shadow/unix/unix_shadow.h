#include <stdbool.h>
#include <unistd.h>

typedef struct pids __pids;

struct pids
{
    char* desc;
};

typedef struct fds __fds;

struct fds
{
    char* desc;
};

#define SHADOW_FD_COUNT 5
#define SHADOW_PID_COUNT 2

__fds __fd_shadow_list[SHADOW_FD_COUNT];
__pids __pid_shadow_list[SHADOW_PID_COUNT];

void unix_shadow_init();
bool prop_is_open_fd(int fd);
bool prop_is_valid_unix_pid(pid_t pid);

bool prop_sighandler_set();
void call_sighandler(int sig);
