#include "uefi_map.h"
#include "types.h"
#include "physical.h"

#define EFI_CONVENTIONAL_MEMORY 7

void parse_uefi_memory_map(Memory *memory, UsableMemoryMap *memory_map) {

    memory_map->region_count = 0;
    u64 region_base = 0;
    
    while (region_base < memory->map_size) {
    
        MemoryMapDescriptor *descriptor = (MemoryMapDescriptor *)((u8 *)memory->map + region_base);
    
        if (descriptor->type == EFI_CONVENTIONAL_MEMORY) {
            MemoryRegion *region = &memory_map->regions[memory_map->region_count];
            region->base = descriptor->physical_start;
            region->size = descriptor->number_of_pages * PAGE_SIZE;
            memory_map->region_count++;
        }
    
        region_base += memory->map_descriptor_size;
    
    }

}
