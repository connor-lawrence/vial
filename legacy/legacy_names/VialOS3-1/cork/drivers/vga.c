#include "vga.h"
#include "../cork.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

static char screen_text_buffer[VGA_HEIGHT][VGA_WIDTH];
static uint16_t screen_color_buffer[VGA_HEIGHT][VGA_WIDTH];

#define VGA_VERTICAL_INDENT 1
#define VGA_INDENT 2

static int cursor_y = 0;
static int cursor_x = 0;

void vga_init() {
    vga_clear_screen();
}

void vga_print(const char* string, uint16_t color) {
    while (*string) {
        if (*string == '\n') {
            vga_newline();
        } else {
            screen_text_buffer[cursor_y][cursor_x] = *string;
            screen_color_buffer[cursor_y][cursor_x] = color;
            cursor_x++;
            if (cursor_x >= VGA_WIDTH) {
                vga_newline();
                cursor_x = cursor_x + VGA_INDENT;
            }
        }
        string++;
    }
}

void vga_newline() {
    if (cursor_y >= VGA_HEIGHT) {
        vga_scroll();
    } else {
    cursor_y++;
    cursor_x = VGA_INDENT;
    }
}

void vga_clear_line() {
    for (int x = 0; x < VGA_WIDTH; x++) {
        screen_text_buffer[cursor_y][x] = ' ';
        screen_color_buffer[cursor_y][x] = 0x07;
    }
}

void vga_clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        cursor_y = y;
        vga_clear_line();
    }
    cursor_y = VGA_VERTICAL_INDENT;
    cursor_x = VGA_INDENT;
}

void vga_scroll() {
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 1; x < VGA_WIDTH; x++) {
            screen_text_buffer[y - 1][x] = screen_text_buffer[y][x];
            screen_color_buffer[y - 1][x] = screen_color_buffer[y][x];
        }
    }
    cursor_y = VGA_HEIGHT - 1;
    vga_clear_line();
    cursor_x = VGA_INDENT;
}

void vga_render() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            uint16_t color = screen_color_buffer[y][x];
            char character = screen_text_buffer[y][x];
            VGA_MEMORY[y * VGA_WIDTH + x] = (color << 8) | character;
        }
    }
}