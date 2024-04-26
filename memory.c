#include <stdlib.h>

#include "memory.h"

void *
reallocate(void *pointer, size_t old_size, size_t new_size)
{
    void *r = NULL;

    if (new_size == 0) {
        free(pointer);
        return NULL;
    }

    r = realloc(pointer, new_size);
    if (!r) {
        exit(1);
    }
    return r;
}