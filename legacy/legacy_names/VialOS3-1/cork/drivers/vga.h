#ifndef VGA_H
#define VGA_H

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

void vga_init();
void vga_print(const char* string, uint16_t color);
void vga_newline();
void vga_clear_line();
void vga_clear_screen();
void vga_scroll();
void vga_render();

typedef enum {
    VGA_BLACK = 0,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_LIGHT_GRAY,
    VGA_DARK_GRAY,
    VGA_LIGHT_BLUE,
    VGA_LIGHT_GREEN,
    VGA_LIGHT_CYAN,
    VGA_LIGHT_RED,
    VGA_LIGHT_MAGENTA,
    VGA_YELLOW,
    VGA_WHITE
} vga_color;

#endif