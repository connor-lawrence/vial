#include "vga.h"
#include "../cork.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

static char screen_text_buffer[VGA_HEIGHT][VGA_WIDTH];
static uint16_t screen_color_buffer[VGA_HEIGHT][VGA_WIDTH];

static char screen_deleteable_filter[VGA_HEIGHT][VGA_WIDTH];  // 0 = non-deleteable, 1 = deleteable

#define VGA_VERTICAL_INDENT 1
#define VGA_INDENT 2

static int cursor_y = 0;
static int cursor_x = 0;

#define CURSOR_CHARACTER '_'

void vga_init() {
    vga_clear_screen();
}

void vga_print(const char* string, uint16_t color, const int filter) {
    if (string[0] == '\n' && string[1] == '\0') {
        print(" ", VGA_LIGHT_GRAY, 1);
        vga_newline();
        return;
    } else {
        while (*string) {
            if (*string == '\n') {
                vga_newline();
            } else {
                screen_text_buffer[cursor_y][cursor_x] = *string;
                screen_color_buffer[cursor_y][cursor_x] = color;
                screen_deleteable_filter[cursor_y][cursor_x] = filter;
                cursor_x++;
                if (cursor_x >= VGA_WIDTH) {
                    vga_newline();
                    vga_indent();
                }
            }
            string++;
        }
    }
}

void vga_newline() {
    screen_text_buffer[cursor_y][cursor_x] = ' ';
    screen_color_buffer[cursor_y][cursor_x] = 0x07;
    if (cursor_y >= VGA_HEIGHT - 1) {
        vga_scroll();
    } else {
    cursor_y++;
    cursor_x = 0;
    vga_indent();
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
    cursor_x = 0;
    vga_indent();
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
    cursor_x = 0;
    vga_indent();
}

void vga_draw_cursor() {
    screen_text_buffer[cursor_y][cursor_x] = CURSOR_CHARACTER;
    screen_color_buffer[cursor_y][cursor_x] = VGA_WHITE;
}

void vga_backspace() {   // ADD LINE WRAPPING
    int cursor_x_buffer = cursor_x;
    int cursor_y_buffer = cursor_y;
    screen_text_buffer[cursor_y][cursor_x] = ' ';
    screen_color_buffer[cursor_y][cursor_x] = 0x07;
    while (screen_deleteable_filter[cursor_y][cursor_x] == 0) {
        screen_deleteable_filter[cursor_y][cursor_x] = 0;
        cursor_x--;
        if (cursor_x < VGA_INDENT) {
            cursor_x = VGA_WIDTH - 1;
            cursor_y--;
            if (cursor_y < VGA_VERTICAL_INDENT) {
                cursor_y = cursor_y_buffer;
                cursor_x = cursor_x_buffer;
                break;
            }
        }
    }
    screen_text_buffer[cursor_y][cursor_x] = ' ';
    screen_color_buffer[cursor_y][cursor_x] = 0x07;
    screen_deleteable_filter[cursor_y][cursor_x] = 0;
    vga_draw_cursor();
    
}

void vga_indent() {
    cursor_x = cursor_x + VGA_INDENT;
    screen_deleteable_filter[cursor_y][cursor_x - 1] = 0;
    screen_deleteable_filter[cursor_y][cursor_x - 2] = 0;
}

void vga_render() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            uint16_t color = screen_color_buffer[y][x];
            char character = screen_text_buffer[y][x];
            VGA_MEMORY[y * VGA_WIDTH + x] = (color << 8) | character;
        }
    }
    vga_draw_cursor();
}