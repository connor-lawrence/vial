#include "cork.h"
#include "../vial/vial.h"

typedef unsigned short u16;

#define VIDEO_MEMORY ((volatile u16*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_SIZE (VGA_WIDTH * VGA_HEIGHT)

void vga_clear() {
    for (int i = 0; i < VGA_SIZE; i++) {
        VIDEO_MEMORY[i] = (0x07 << 8) | ' ';
    }
    static int cursor_location = 0;
}

static int cursor_location = 0;

void vga_newline() {
    cursor_location += 80 - (cursor_location % 80);
}

void vga_put_char(char input, char color) {
    VIDEO_MEMORY[cursor_location++] = (color << 8) | input;
}

void vga_print(const char *text, char color) {
    for (int i = 0; text[i] != '\0'; i++) {
        vga_put_char(text[i], color);
    }
}

void kernel_main() {
    char green = 0x02;
    char blue = 0x09;
    char gray = 0x07;
    char white = 0x0F;
    vga_newline();
    vga_print("  [", gray);
    vga_print("VialOS/cork/cork.c", green);
    vga_print("] ", gray);
    vga_print("kernel_main() ", green);
    vga_print("called, calling ", gray);
    vga_print("os_main()", blue);
    vga_print("...", gray);
    vga_newline();
    os_main();
}