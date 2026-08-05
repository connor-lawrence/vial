#include "print.h"
#include "types.h"

void debug_putc(char c) {
    __asm__ volatile ("outb %%al, $0xE9" : : "a"(c));
}

void debug_print(const char *str) {
    while (*str) {
        debug_putc(*str);
        str++;
    }
}

void debug_print_int(const char *before, const u64 x, const char *after) {
    debug_print(before);
    u64 n = x;
    char buffer[21];
    u32 i = 0;
    if (!x) {
        debug_putc('0');
    }
    while (n) {
        buffer[i] = (char)(n % 10) + 48;
        n /= 10;
        i++;
    }
    while (i) {
        debug_putc(buffer[--i]);
    }
    debug_print(after);
}

void debug_print_hex(const char *before, const u64 x, const char *after) {
    debug_print(before);
    debug_print("0x");
    u32 digit = 0;
    for (int i = 15; i >= 0; i--) {
        digit = (x >> (i * 4)) & 0xF;
        if (digit <= 9) {
            debug_putc((char)digit + 48);
        } else {
            debug_putc((char)digit + 55);
        }
    }
    debug_print(after);
}
