#include "dPartition.h"
#include <stdio.h>

void show_dPartition(dPartition* dp) {
    printf("dPartition(start=%p, size=0x%x, firstFreeStart=%p)\n", 
        dp, (unsigned)dp->size, dp->firstFreeStart);
}

void showEMB(EMB* emb) {
    printf("EMB(start=%p, free=0x%x, size=0x%x, nextStart=%p, prevStart=%p)\n",
             emb, (unsigned)emb->free, (unsigned)emb->size, emb->nextStart, emb->prevStart);
}

// return NULL if failed, otherwise start address
dPartition* dPartitionInit(void* start, size_t totalSize) {
    if (totalSize <= sizeof(EMB) + sizeof(dPartition)) return NULL;
    dPartition* handle = (dPartition*)start;
    EMB* emb = (EMB*)(start + sizeof(dPartition));
    *handle = (dPartition){.size = totalSize - sizeof(dPartition), .firstFreeStart = emb};
    *emb = (EMB){.size = handle->size - sizeof(EMB), .free = 1, .prev = 0, .nextStart = 0};
    return start;
}

void dPartitionWalkByAddr(dPartition* d_par) {
    show_dPartition(d_par);
    for (void* i = (void*)d_par + sizeof(dPartition); 
        i - (void*)d_par - sizeof(dPartition) < d_par->size;
        i = ((EMB*)i)->size + i + sizeof(EMB))
        showEMB((EMB*)i);
}

const unsigned long align = 4;

// Using first meet allocation algorithm
void* dPartitionAlloc(dPartition* d_par, size_t size) {
    if (size == 0) return NULL;
    EMB* emb = d_par->firstFreeStart;
    if (size % align) size = (size / align + 1) * align;
    int flag = 0;
    for (; emb; emb = emb->nextStart) {
        if (emb->size >= size + sizeof(EMB)
            || emb->size == size) { flag = 1; break; }
    }
    if (!flag) return NULL;
    if (emb->size == size) {
        if (emb->prevStart == 0) // Head of the list.
            d_par->firstFreeStart = emb->nextStart;
        else emb->prevStart->nextStart = emb->nextStart;
        emb->free = 0;
    }
    else {
        void* new_emb_pos = (void*)(emb + 1) + size;
        *(EMB*)(new_emb_pos) = (EMB){.size = emb->size - size - sizeof(EMB), .free = 1,
                .nextStart = emb->nextStart, .prev = emb, .prevStart = emb->prevStart};
        emb->size = size; emb->free = 0;
        if (emb->prevStart == 0) d_par->firstFreeStart = new_emb_pos;
        else emb->prevStart->nextStart = (EMB*)new_emb_pos;
    }
    return (void*)(emb + 1);
}

// return 0 if success, 1 if error
int dPartitionFree(dPartition* dP, void* start) {
    void* max_len = (void*)(dP + 1) + dP->size;
    if (start >= max_len) return 1;
    EMB* emb = (EMB*)start - 1;
    if (emb->free) return 1;
    EMB* next = (EMB*)(start + emb->size);
    if (start + emb->size < max_len && next->free) {
        // First remove the next block.
        if (next->prevStart) next->prevStart->nextStart = next->nextStart;
        else dP->firstFreeStart = NULL;
        if (next->nextStart) next->nextStart->prevStart = next->prevStart;
        // Merge the next block into the current one.
        emb->size += sizeof(EMB) + next->size;
        if ((void*)(next + 1) + next->size < max_len)
            ((EMB*)((void*)(next + 1) + next->size))->prev = emb;
    }
    EMB* prev = emb->prev;
    if (prev && prev->free) {
        prev->size += sizeof(EMB) + emb->size;
        if (start + emb->size < max_len)
            ((EMB*)(start + emb->size))->prev = prev;
    }
    else {
        // Insert emb to the head of the list.
        emb->nextStart = dP->firstFreeStart;
        emb->prevStart = 0;
        emb->prev = 0;
        emb->free = 1;
        if (dP->firstFreeStart)
            dP->firstFreeStart->prevStart = emb;
        dP->firstFreeStart = emb;
    }
    return 0;
}
