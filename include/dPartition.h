#pragma once

#include <stddef.h>

// data structure of memory block
// block size is dynamic
typedef struct EMB {
    size_t size;
    size_t free;
    // start address of last emb, not necessary to be free,
    // used while freeing memory
    struct EMB* prev; 
    struct EMB* nextStart;
    struct EMB* prevStart; // last free block in list
} EMB;

// data structure of memory allocation list
// block size is dynamic
typedef struct dPartition {
    size_t size;
    EMB* firstFreeStart; 
} dPartition;

#ifdef __cplusplus
extern "C" {
#endif

extern void show_dPartition(dPartition* dp);
extern void showEMB(EMB* emb);
// return NULL if failed, otherwise start address
extern dPartition* dPartitionInit(void* start, size_t totalSize);
extern void dPartitionWalkByAddr(dPartition* d_par);
// Using first meet allocation algorithm
extern void* dPartitionAlloc(dPartition* d_par, size_t size);
// return 0 if success, 1 if error
extern int dPartitionFree(dPartition* dP, void* start);

#ifdef __cplusplus
}
#endif
