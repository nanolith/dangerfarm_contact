#pragma once
#include <stdint.h>

typedef struct contact_form contact_form;

struct contact_form
{
    uint64_t name_size;
    uint64_t email_size;
    uint64_t comment_size;
    char data[];
};
