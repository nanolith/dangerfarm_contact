#include <stdbool.h>

enum desc_type
{
    DESC_TYPE_ANY = 0,
    DESC_TYPE_SOCKET = 1,
    DESC_TYPE_FILE = 2
};

typedef struct desc desc;
struct desc
{
    int type;
    int flags;
};

#define SHADOW_DESC_COUNT 4

extern desc* unistd_desc_array[SHADOW_DESC_COUNT];

bool prop_is_valid_unix_desc(int d, int type, int flags);
