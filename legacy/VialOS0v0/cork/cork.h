#ifndef CORK_H
#define CORK_H

void vga_clear();
void vga_newline();
void vga_put_char(char input, char color);
void vga_print(const char *text, char color);
void kernel_main();

#endif