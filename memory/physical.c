#include "physical.h"
#include "types.h"
#include "uefi_map.h"
#include "print.h"
#include "panic.h"

static void set_page(u64 page, bool value);

static PhysicalMemoryState *physical_memory_state = NULL;

void physical_memory_init(const UsableMemoryMap *memory_map) {

    u64 total_pages = 0;
    u64 memory_region = 0;

    // Find the total number of pages to go into the bitmap
    for (u64 i = 0; i < memory_map->region_count; i++) {
        total_pages += memory_map->regions[i].size / PAGE_SIZE;
    }

    u64 bitmap_size = (total_pages + 7) / 8;

    // Find the first available space for physical memory state and regions and place it there
    for (u64 i = 0; i < memory_map->region_count; i++) {
        if (memory_map->regions[i].size >= sizeof(PhysicalMemoryState) + (sizeof(MemoryRegion) * memory_map->region_count) + bitmap_size) {
            physical_memory_state = (PhysicalMemoryState *)memory_map->regions[i].base;
            memory_region = i;
            break;   
        }
    }
    if (physical_memory_state == NULL) {
        panic("[Physical Memory Init] Not enough space for physical memory state");
    }

    physical_memory_state->page_count = total_pages;
    physical_memory_state->memory_map.region_count = memory_map->region_count;

    // Place the memory map regions after the physical memory state
    MemoryRegion *memory_regions = (MemoryRegion *)((u8 *)physical_memory_state + sizeof(PhysicalMemoryState));
    physical_memory_state->memory_map.regions = memory_regions;

    // Copy the memory map regions into their permanent place
    for (u64 i = 0; i < physical_memory_state->memory_map.region_count; i++) {
        physical_memory_state->memory_map.regions[i].base = memory_map->regions[i].base;
        physical_memory_state->memory_map.regions[i].size = memory_map->regions[i].size;
    }

    // Place the bitmap after the physical memory state and map regions
    u8 *bitmap = (u8 *)((u8 *)physical_memory_state + sizeof(PhysicalMemoryState) + (sizeof(MemoryRegion) * physical_memory_state->memory_map.region_count));
    physical_memory_state->bitmap = bitmap;
    physical_memory_state->bitmap_size = bitmap_size;

    // Mark all memory as free (REPLACE WITH MEMSET LATER!)
    for (u64 i = 0; i < bitmap_size; i++) {
        bitmap[i] = 0;
    }

    // Mark physical memory state, map regions, and bitmap as used
    u64 pages_before_region_start = 0;
    for (u64 i = 0; i < memory_region; i++) {
        pages_before_region_start += physical_memory_state->memory_map.regions[i].size / PAGE_SIZE;
    }
    u64 reserve_size = ((sizeof(PhysicalMemoryState) + (sizeof(MemoryRegion) * physical_memory_state->memory_map.region_count) + bitmap_size) + PAGE_SIZE - 1) / PAGE_SIZE;
    for (u64 i = 0; i < reserve_size; i++) {
        set_page(pages_before_region_start + i, true);
    }

}

u64 physical_allocate_page(void) {
    for (u64 i = 0; i < physical_memory_state->page_count; i++) {
        u64 byte_index = i / 8;
        u64 bit_index = i % 8;
        if (!(physical_memory_state->bitmap[byte_index] & (1 << bit_index))) {
            set_page(i, true);

            // Convert bitmap page to address
            u64 remaining_pages = i;
            for (u64 j = 0; j < physical_memory_state->memory_map.region_count; j++) {
                if (remaining_pages < physical_memory_state->memory_map.regions[j].size / PAGE_SIZE) {
                    return physical_memory_state->memory_map.regions[j].base + (remaining_pages * PAGE_SIZE);
                } else {
                    remaining_pages -= physical_memory_state->memory_map.regions[j].size / PAGE_SIZE;
                }
            }

        }
    }
    panic("[Physical Page Allocator] Not enough memory to allocate page");
}

static void set_page(u64 page, bool value) {
    u64 byte_index = page / 8;
    u64 bit_index = page % 8;
    if (value) {
        physical_memory_state->bitmap[byte_index] |= (1 << bit_index);
    } else {
        physical_memory_state->bitmap[byte_index] &= (u8)~(1 << bit_index);
    }
}
