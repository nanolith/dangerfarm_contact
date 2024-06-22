#pragma once

#include <stdbool.h>
#include <stdint.h>

enum ctool_command
{
    CTOOL_COMMAND_NONE                                          = 0,
    CTOOL_COMMAND_APPEND                                        = 1,
    CTOOL_COMMAND_GET_COUNT                                     = 2,
};

typedef struct ctool_context ctool_context;
struct ctool_context
{
    char* db_path;
    char* socket_path;
    int sock;
    uint64_t form_id;
    bool form_id_set;
};
