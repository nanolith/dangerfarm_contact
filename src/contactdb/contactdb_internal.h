#pragma once

#include <stdint.h>

#define DATABASE_CAPABILITY_CONTACT_FORM_APPEND                 0x0001
#define DATABASE_CAPABILITY_CONTACT_FORM_GET                    0x0002
#define DATABASE_CAPABILITY_CONTACT_FORM_DELETE                 0x0004
#define DATABASE_CAPABILITY_CONTACT_FORM_COUNT_GET              0x0008
#define DATABASE_CAPABILITY_CONTACT_FORM_LIST_GET               0x0010

typedef struct contactdb_context contactdb_context;
struct contactdb_context
{
    char* db_path;
    char* socket_path;
    uint64_t root_capabilities;
};
