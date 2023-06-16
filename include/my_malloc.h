#pragma once

#define MEMORY_SIZE 10240

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void* my_malloc(size_t size);
extern void* my_realloc(void* p, size_t new_size);
extern int my_free(void* p);

#ifdef __cplusplus
}
#endif
