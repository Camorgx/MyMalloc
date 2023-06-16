#pragma once

#define MEMORY_SIZE 10240

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void* my_malloc(size_t size);

#ifdef __cplusplus
}
#endif
