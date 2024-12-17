#pragma once

#include <stdbool.h>
#include <unistd.h>

bool prop_is_open_fd(int fd);
bool prop_is_valid_unix_pid(pid_t pid);
