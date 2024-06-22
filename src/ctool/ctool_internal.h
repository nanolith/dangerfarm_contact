#pragma once

typedef struct ctool_context ctool_context;
struct ctool_context
{
    char* db_path;
    char* socket_path;
    int sock;
};
