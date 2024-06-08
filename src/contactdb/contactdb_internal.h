#pragma once

#include <stdint.h>

#define DATABASE_CAPABILITY_CONTACT_FORM_APPEND                 1
#define DATABASE_CAPABILITY_CONTACT_FORM_GET                    2
#define DATABASE_CAPABILITY_CONTACT_FORM_DELETE                 4
#define DATABASE_CAPABILITY_CONTACT_FORM_COUNT_GET              8

typedef struct contactdb_context contactdb_context;
struct contactdb_context
{
    char* db_path;
    char* socket_path;
    uint64_t root_capabilities;
};
