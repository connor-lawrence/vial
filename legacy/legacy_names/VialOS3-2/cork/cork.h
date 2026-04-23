#ifndef CORK_H
#define CORK_H

#include "cpu/cpu.h"
#include "drivers/drivers.h"

#include "../vial/vial.h"

void kernel_init();
void kernel_main();
void keyboard_handler(char key);

void print(const char* string, uint16_t color, const int filter);
void clear_line();
void clear_screen();
void backspace();

#endif