#include "vga.h"
#include "../cork.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

static char screen_text_buffer[VGA_HEIGHT][VGA_WIDTH];
static uint16_t screen_color_buffer[VGA_HEIGHT][VGA_WIDTH];

#define VGA_VERTICAL_BORDER 1
#define VGA_RIGHT_BORDER_WIDTH 1
#define VGA_INDENT 2

static int cursor_y = 0;
static int cursor_x = 0;

#define CURSOR_CHARACTER '_'

void vga_init() {
    vga_clear_screen();
    vga_indent();
}

void vga_print_char(char character, uint16_t color, int x, int y) {
    VGA_MEMORY[y * VGA_WIDTH + x] = (color << 8) | character;
}

void vga_print_string(const char* string, uint16_t color, int x, int y) {
    cursor_x = x;
    cursor_y = y;
    while (*string) {
        if (cursor_x >= VGA_WIDTH - VGA_RIGHT_BORDER_WIDTH) {
            vga_newline();
        }
        vga_print_char(*string, color, cursor_x, cursor_y);
        cursor_x++;
        string++;
    }
}

void vga_newline() {
    cursor_y++;
    if (cursor_y >= VGA_HEIGHT - VGA_VERTICAL_BORDER + 1) {
        vga_scroll(1);
        cursor_y = VGA_HEIGHT - VGA_VERTICAL_BORDER;
    }
    vga_indent();
}

void vga_clear_line() {
    for (int x = 0; x < VGA_WIDTH; x++) {
        screen_text_buffer[cursor_y][x] = ' ';
        screen_color_buffer[cursor_y][x] = VGA_LIGHT_GRAY;
    }
    cursor_x = 0;
    vga_indent();
}

void vga_scroll(int delta) {
    if (delta > 1) delta = 1;
    if (delta < -1) delta = -1;
    char new_screen_text_buffer[VGA_HEIGHT][VGA_WIDTH];
    uint16_t new_screen_color_buffer[VGA_HEIGHT][VGA_WIDTH];
    for (int y = delta; y < VGA_HEIGHT; y++) { // FIX ME: THIS CAUSES A BUG IF delta < 0
        for (int x = 0; x < VGA_WIDTH; x++) {
            new_screen_text_buffer[y - delta][x] = screen_text_buffer[y][x];
            new_screen_color_buffer[y - delta][x] = screen_color_buffer[y][x];
        }
    }
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            screen_text_buffer[y][x] = new_screen_text_buffer[y][x];
            screen_color_buffer[y][x] = new_screen_color_buffer[y][x];
        }
    }
    if (delta == 1) {
        cursor_y = VGA_HEIGHT - VGA_VERTICAL_BORDER - 1;
        vga_clear_line();
    } else if (delta == -1) {
        cursor_y = VGA_VERTICAL_BORDER;
        vga_clear_line();
    }
}

void vga_clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            screen_text_buffer[y][x] = ' ';
            screen_color_buffer[y][x] = VGA_LIGHT_GRAY;
        }
    }
    vga_set_cursor(VGA_INDENT, VGA_VERTICAL_BORDER);
}

void vga_indent() {
    for (int i = 0; i < VGA_INDENT; i++) {
        screen_text_buffer[cursor_y][i] = ' ';
        screen_color_buffer[cursor_y][i] = VGA_LIGHT_GRAY;
    }
    cursor_x = cursor_x + VGA_INDENT;
}

void vga_set_cursor(int x, int y) {
    if (x < 0) x = 0;
    if (x >= VGA_WIDTH) x = VGA_WIDTH - 1;
    if (y < 0) y = 0;
    if (y >= VGA_HEIGHT) y = VGA_HEIGHT - 1;
    cursor_x = x;
    cursor_y = y;
}

void vga_render() {
    vga_clear_screen();
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_print_char(screen_text_buffer[y][x], screen_color_buffer[y][x], x, y);
        }
    }
    vga_render_cursor();
}

void vga_render_cursor() {
    vga_print_char(CURSOR_CHARACTER, VGA_WHITE, cursor_x, cursor_y);
}