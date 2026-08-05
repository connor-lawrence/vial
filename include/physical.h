#pragma once
#include "types.h"
#include "boot.h"

typedef struct {
    u64 base;
    u64 size;
} MemoryRegion;

typedef struct {
    MemoryRegion *regions;
    u64 region_count;
} UsableMemoryMap;

typedef struct {
    u8 *bitmap;
    u64 bitmap_size;
    u64 page_count;
    UsableMemoryMap memory_map;
} PhysicalMemoryState;

void physical_memory_init(const UsableMemoryMap *map);
u64 physical_allocate_page(void);
