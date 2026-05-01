#include "vga.h"
#include "types.h"

/*
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

static char screen_text_buffer[VGA_HEIGHT][VGA_WIDTH];
static u16 screen_color_buffer[VGA_HEIGHT][VGA_WIDTH];

void vga_init() {
    vga_clear_screen();
}

void vga_print_char(char character, u16 color, int x, int y) {
    screen_text_buffer[y][x] = character;
    screen_color_buffer[y][x] = color;
}

void vga_write_char(char character, u16 color, int x, int y) {
    VGA_MEMORY[y * VGA_WIDTH + x] = (color << 8) | character;
}

void vga_render() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_write_char(screen_text_buffer[y][x], screen_color_buffer[y][x], x, y);
        }
    }
}
*/