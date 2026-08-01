#include "physical.h"
#include "types.h"
#include "boot.h"

#include "serial.h"

#define PAGE_SIZE 4096
#define MAX_REGIONS 128
#define EFI_CONVENTIONAL_MEMORY 7

static MemoryRegion memory_regions[MAX_REGIONS];
static u64 region_count = 0;

// For bump allocator
static u64 current_region = 0;
static u64 current_offset = 0;

static void parse_memory_map(Memory *memory);

void memory_init(Memory *memory) {

    current_region = 0;
    current_offset = 0;

    parse_memory_map(memory);

    serial_print("Physically reserving kernel (if needed)...\n");
    u64 pages = (memory->kernel_size + PAGE_SIZE - 1) / PAGE_SIZE;
    physical_reserve_region(memory->kernel_base, pages * PAGE_SIZE);

    serial_print_int("\n   Final memory regions: ", region_count, "\n\n");

    for (u64 i = 0; i < region_count; i++) {
        MemoryRegion *region = &memory_regions[i];
        serial_print_int("Memory region ", i + 1, " ");
        serial_print_hex("@ ", region->base, " ");
        serial_print_int("- ", region->size / PAGE_SIZE, " pages\n");
    }

}

static void parse_memory_map(Memory *memory) {

    region_count = 0;
    u64 region_base = 0;
    u64 usable_pages = 0;

    serial_print("   Conventional memory regions from EFI:\n\n");

    while (region_base < memory->map_size && region_count < MAX_REGIONS) {

        MemoryMapDescriptor *descriptor = (MemoryMapDescriptor *)((u8 *)memory->map + region_base);

        if (descriptor->type == EFI_CONVENTIONAL_MEMORY) {

            memory_regions[region_count].base = descriptor->physical_start;
            memory_regions[region_count].size = descriptor->number_of_pages * PAGE_SIZE;

            region_count++;

            serial_print_int("Memory region ", region_count, " ");
            serial_print_hex("@ ", descriptor->physical_start, " - ");
            serial_print_int("", descriptor->number_of_pages, " pages\n");

            usable_pages += descriptor->number_of_pages;

        }

        region_base += memory->map_descriptor_size;

    }

    serial_print_int("\nTotal usable memory: ", usable_pages, " pages, ");
    serial_print_int("", usable_pages / 256, " MiB\n\n");

}

void physical_reserve_region(u64 base, u64 size) {

    u64 reserved_region_end = base + size;

    serial_print_hex("Reserving region @ ", base, "");
    serial_print_int(", ", size / PAGE_SIZE, " pages\n");

    for (u64 i = 0; i < region_count; i++) {

        MemoryRegion *region = &memory_regions[i];

        u64 region_end = region->base + region->size;

        if (reserved_region_end <= region->base || base >= region_end) {

            continue;

        } else if (base <= region->base && reserved_region_end >= region_end) {

            memory_regions[i] = memory_regions[region_count - 1];
            region_count--;
            i--;

        } else if (base <= region->base && reserved_region_end < region_end) {

            region->base = reserved_region_end;
            region->size = region_end - reserved_region_end;

        } else if (base > region->base && reserved_region_end >= region_end) {

            region->size = base - region->base;

        } else if (base > region->base && reserved_region_end < region_end) {

            if (region_count >= MAX_REGIONS) {
                continue;
            }

            region->size = base - region->base;

            MemoryRegion *new_region = &memory_regions[region_count++];

            new_region->base = reserved_region_end;
            new_region->size = region_end - reserved_region_end;

        }

    }

}

void* physical_allocate_page() {

    if (current_region >= region_count) {
        return NULL;
    }
    
    if (current_offset + PAGE_SIZE > memory_regions[current_region].size) {
        current_offset = 0;
        current_region++;
    }

    if (current_region >= region_count) {
        return NULL;
    }

    u64 address = memory_regions[current_region].base + current_offset;

    current_offset += PAGE_SIZE;

    return (void*)address;

}
