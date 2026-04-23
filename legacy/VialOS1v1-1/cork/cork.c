#include "cork.h"
#include "cpu/cpu.h"
#include "drivers/drivers.h"

#include "../vial/vial.h"

void kernel_init() {
    vga_init();
    kernel_main();
}

void kernel_main() {
    os_init();
    while (1) {
        keyboard_poll();
        vga_render();
    }
}

void keyboard_handler(char key) {
    os_keyboard_handler(key);
    //char str[2] = {key, '\0'};
    //print(str, VGA_YELLOW);
}

// Forwarding

void print(const char* string, uint16_t color) {
    vga_print(string, color);
}

void clear_screen() {
    vga_clear_screen();
}