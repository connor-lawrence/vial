#include "init.h"
#include "types.h"
#include "boot.h"
#include "uefi_map.h"
#include "physical.h"
#include "print.h"

void kernel_init(BootInfo *boot_info) {

    debug_print("\nHello from Iris!\n\n");

    // Parse UEFI memory map
    UsableMemoryMap usable_memory;
    parse_uefi_memory_map(&boot_info->memory, &usable_memory);

    // Print memory regions and total memory
    u64 available_pages = 0;
    debug_print_int("Memory regions: ", usable_memory.region_count, "\n");
    for (u32 i = 0; i < usable_memory.region_count; i++) {
        debug_print_int("Region ", i + 1, " ");
        debug_print_hex("@ ", (u64)usable_memory.regions[i].base, ", ");
        debug_print_int("", usable_memory.regions[i].size / PAGE_SIZE, " pages\n");
        available_pages += usable_memory.regions[i].size / PAGE_SIZE;
    }
    debug_print_int("\nTotal memory: ", available_pages, " ");
    debug_print_int("pages, ", available_pages * PAGE_SIZE / 1048576, " MiB\n\n");

    // Initialize physical memory manager
    physical_memory_init(&usable_memory);

    debug_print_hex("Test page allocated at ", physical_allocate_page(), "\n\n");

    /*
    // Test that allocates a million pages
    debug_print("Allocation test:\n");
    u64 prev = 0;
    for (u64 i = 0; i < 1000000; i++) {
        u64 curr = physical_allocate_page();
        if (prev == 0 || curr != prev + PAGE_SIZE || i % 10000 == 0) {
            debug_print_hex("Now at ", curr, " after allocation ");
            debug_print_int("# ", i, "\n");
        }
        prev = curr;
    }
    */

    // Halt
    debug_print("Iris halting.\n");
    while (1) {
        __asm__ volatile ("hlt");
    }

}
