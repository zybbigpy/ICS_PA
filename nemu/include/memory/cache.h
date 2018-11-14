#ifndef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"

#define CACHELINE_SIZE_B 64   // 64 byte cacheline
#define CACHE_SIZE_B 1024*64  // 64 kbyte cache

typedef struct {
    struct {
        // valid bit
        uint32_t validBit:1;
        // flag
        uint32_t flag:23;
        // no use
        uint32_t dummy:8;
    } bitAndFlag;
    // 64 bytes for content
    uint8_t content[CACHELINE_SIZE_B];
}CacheLine;

// L1 cache
extern CacheLine L1_dcache[];

// init cache and set all valid bits zero
void init_cache();

// read cache
uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache);

// write cache
void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache);

#endif