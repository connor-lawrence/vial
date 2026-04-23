#include "cork.h"
#include "cpu/cpu.h"
#include "drivers/drivers.h"

#include "../vial/vial.h"

void kernel_init() {
    vga_init();
    clear_screen();

    print("[ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] VGA initialized...\n", VGA_LIGHT_GRAY);

    kernel_main();
}

void kernel_main() {
    print("[ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] Kernel fully initialized, starting OS...\n", VGA_LIGHT_GRAY);
    
    os_init();

    print("[ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] TESTING KEYBOARD...\n\n", VGA_LIGHT_GRAY);

    uint8_t scancode = inb(0x60);
    uint16_t last = 0;

    while (1) {
        
        /* SCAN KEYBOARD */
        uint8_t scancode = inb(0x60);
        if (scancode == last) continue;
        last = scancode;
        if (scancode & 0x80) {
            // release marker
        }
        else {
            char key = scancode_to_ascii[scancode];
            if (key) {
                keyboard_handler(key);
            }
        }

        vga_render();

    }
}

void keyboard_handler(char key) {
    char str[2] = {key, '\0'};
    print(str, VGA_YELLOW);
    
}

/* Forwarding */

void print(const char* string, uint16_t color) {
    vga_print(string, color);
}

void clear_screen() {
    vga_clear();
}