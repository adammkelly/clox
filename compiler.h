#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "vm.h"

void compile(const char* source, chunk_t *chunk);

#endif