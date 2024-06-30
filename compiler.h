#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "object.h"
#include "vm.h"

obj_function_t* compile(const char* source);
void mark_compiler_roots();

#endif