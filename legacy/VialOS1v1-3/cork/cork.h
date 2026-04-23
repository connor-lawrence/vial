#ifndef CORK_H
#define CORK_H

#include "cpu/cpu.h"
#include "drivers/drivers.h"

#include "../vial/vial.h"

void kernel_init();
void kernel_main();
void keyboard_handler(char key);

void print(const char* string, uint16_t color, int x, int y);
void newline();
void clear_line();
void scroll(int delta);
void clear_screen();
void backspace();

#endif