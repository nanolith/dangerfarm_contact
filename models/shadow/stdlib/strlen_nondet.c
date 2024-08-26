#include <stddef.h>

size_t nondet_size();

size_t strlen(const char *s)
{
    return nondet_size();
}
