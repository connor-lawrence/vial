#pragma once
#include "types.h"
#include "boot.h"
#include "physical.h"

#define PAGE_SIZE 4096

typedef struct {
    u32 type;
    u32 pad;
    u64 physical_start;
    u64 virtual_start;
    u64 number_of_pages;
    u64 attribute;
} MemoryMapDescriptor;

void parse_uefi_memory_map(Memory *memory, UsableMemoryMap *map);
