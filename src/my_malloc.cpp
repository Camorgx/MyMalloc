#include "dPartition.h"
#include "my_malloc.h"
#include <cstddef>
#include <cstring>

unsigned char data[MEMORY_SIZE];

dPartition* handle = dPartitionInit(data, sizeof(data));

extern "C" {
    void* my_malloc(size_t size) {
        return dPartitionAlloc(handle, size);
    }

    int my_free(void* p) {
        return dPartitionFree(handle, p);
    }

    void* my_realloc(void* p, size_t new_size) {
        if (my_free(p)) return NULL;
        void* pos = my_malloc(new_size);
        size_t old_size = ((EMB*)p - 1)->size;
        size_t copy_size = new_size > old_size ? old_size : new_size;
        memcpy(pos, p, copy_size);
        return pos;
    }
}
