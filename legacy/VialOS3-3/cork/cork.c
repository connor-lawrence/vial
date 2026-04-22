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

void print(const char* string, uint16_t color, int x, int y) {vga_print_string(string, color, x, y);}
void newline() {vga_newline();}
void clear_line() {vga_clear_line();}
void scroll(int delta) {vga_scroll(delta);}
void clear_screen() {vga_clear_screen();}
void indent() {vga_indent();}
void set_cursor(int x, int y) {vga_set_cursor(x, y);}