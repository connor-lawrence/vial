#include "panic.h"
#include "types.h"
#include "print.h"

_Noreturn void panic(const char *message) {
    debug_print("Kernel panic: ");
    debug_print(message);
    debug_print("\n");
    while (1) {
        __asm__ volatile ("hlt");
    }
}
