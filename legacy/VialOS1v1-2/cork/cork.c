#include "cork.h"

void kernel_init() {
    vga_init();
    kernel_main();
    os_init();
}

void kernel_main() {
    while (1) {
        keyboard_poll();
        os_main();
        vga_render();
    }
}

void keyboard_handler(char key) {
    os_keyboard_handler(key);
}

// Forwarding

void print(const char* string, uint16_t color, const int filter) {
    vga_print(string, color, filter);
}

void clear_line() {
    vga_clear_line();
}

void clear_screen() {
    vga_clear_screen();
}

void backspace() {
    vga_backspace();
}