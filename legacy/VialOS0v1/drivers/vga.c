#include "vga.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

static int cursor_x = 0;
static int cursor_y = 0;

void vga_init() {
    vga_clear();
    cursor_x = 0;
    cursor_y = 0;
}

void vga_print(const char* string, uint16_t color) {
    while (*string) {
        if (*string == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            VGA_MEMORY[cursor_y * VGA_WIDTH + cursor_x] = (color << 8) | *string;
            cursor_x++;
            if (cursor_x >= VGA_WIDTH) {
                cursor_x = 0;
                cursor_y++;
            }
        }
        string++;
        if (cursor_y >= VGA_HEIGHT) {
            cursor_y = VGA_HEIGHT - 1; // Clamps to last line
        }
    }
}

void vga_clear() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[y * VGA_WIDTH + x] = (0x07 << 8) | ' ';
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}