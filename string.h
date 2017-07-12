#ifndef __string_h__
#define __string_h__

#include "types.h"

size_t strlen(const char *str)
{
    const char* ptr = str;
    while (*ptr)
        ptr++;

    return (size_t)ptr - (size_t)str;
}

#endif
