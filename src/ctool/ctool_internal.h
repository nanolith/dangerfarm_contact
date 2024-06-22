#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct ctool_context ctool_context;
struct ctool_context
{
    char* db_path;
    char* socket_path;
    int sock;
    uint64_t form_id;
    bool form_id_set;
};
