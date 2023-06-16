#include "dPartition.h"
#include "my_malloc.h"

int main(void) {
    extern dPartition* handle;
    dPartitionWalkByAddr(handle);
    void* p1 = my_malloc(10);
    void* p2 = my_malloc(20);
    void* p3 = my_malloc(30);
    void* p4 = my_malloc(40);
    void* p5 = my_malloc(50);
    dPartitionWalkByAddr(handle);
    my_free(p3);
    dPartitionWalkByAddr(handle);
    return 0;
}
