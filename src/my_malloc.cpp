#include "dPartition.h"
#include "my_malloc.h"
#include <cstddef>

unsigned char data[MEMORY_SIZE];

dPartition* handle = dPartitionInit(data, sizeof(data));

extern "C" {
    void* my_malloc(size_t size) {
        return dPartitionAlloc(handle, size);
    }

    int my_free(void* p) {
        return dPartitionFree(handle, p);
    }
}
