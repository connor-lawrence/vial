#include "vga.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

static char screen_buffer_text[VGA_HEIGHT][VGA_WIDTH];
static uint16_t screen_buffer_color[VGA_HEIGHT][VGA_WIDTH];

#define VGA_START_LINE 1
#define VGA_INDENT 2

static int cursor_x = 0;
static int cursor_y = 0;

void vga_init() {
    vga_clear();
    vga_render();
}

void vga_print(const char* string, uint16_t color) {
    while (*string) {

        if (*string == '\n') {
            cursor_x = VGA_INDENT; // PREFERENCE
            cursor_y++;

        } else {
            screen_buffer_text[cursor_y][cursor_x] = *string;
            screen_buffer_color[cursor_y][cursor_x] = color;
            cursor_x++;

            if (cursor_x >= VGA_WIDTH) {
                cursor_x = 0;
                cursor_y++;
            }
        }
        string++;
        if (cursor_y >= VGA_HEIGHT) {
            vga_scroll();
        }
    }
}

void vga_render() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            uint16_t color = screen_buffer_color[y][x];
            char character = screen_buffer_text[y][x];
            VGA_MEMORY[y * VGA_WIDTH + x] = (color << 8) | character;
        }
    }
}

void vga_clear() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            screen_buffer_text[y][x] = ' ';
            screen_buffer_color[y][x] = 0x07;
        }
    }
    cursor_x = VGA_INDENT; // PREFERENCE
    cursor_y = VGA_START_LINE; // PREFERENCE
}

void vga_scroll() {
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            screen_buffer_text[y - 1][x] = screen_buffer_text[y][x];
            screen_buffer_color[y - 1][x] = screen_buffer_color[y][x];
        }
    }
    // Clear the last line
    for (int x = 0; x < VGA_WIDTH; x++) {
        screen_buffer_text[VGA_HEIGHT - 1][x] = ' ';
        screen_buffer_color[VGA_HEIGHT - 1][x] = 0x07;
    }
    cursor_x = VGA_INDENT; // PREFERENCE
    cursor_y--;
}