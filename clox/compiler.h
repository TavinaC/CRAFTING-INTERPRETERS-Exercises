#ifndef clox_compiler_h
#define clox_compiler_h

#include "object.h"
#include "vm.h"

#define MAX_CASES 256

bool compile(const char* source, Chunk* chunk);

#endif