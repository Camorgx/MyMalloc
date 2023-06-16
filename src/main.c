#include "dPartition.h"
#include "my_malloc.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    extern dPartition* handle;
    puts("Initial:");
    dPartitionWalkByAddr(handle);
    puts("");

    void* p1 = my_malloc(10);
    void* p2 = my_malloc(20);
    void* p3 = my_malloc(30);
    void* p4 = my_malloc(40);
    void* p5 = my_malloc(50);
    printf("p1=%p, ",p1);
    printf("p2=%p, ",p2);
    printf("p3=%p, ",p3);
    printf("p4=%p, ",p4);
    printf("p5=%p\n",p5);
    puts("After malloc:");
    dPartitionWalkByAddr(handle);
    puts("");
    
    my_free(p3);
    puts("After free:");
    dPartitionWalkByAddr(handle);
    puts("");
    
    strcpy(p4, "Hello world!");
    printf("Before realloc, *p4=\"%s\"\n", (char*)p4);
    p4 = my_realloc(p4, 20);
    puts("After realloc:");
    dPartitionWalkByAddr(handle);
    printf("*p4=\"%s\"\n", (char*)p4);
    printf("p1=%p, ",p1);
    printf("p2=%p, ",p2);
    printf("p4=%p, ",p4);
    printf("p5=%p\n",p5);
    return 0;
}
