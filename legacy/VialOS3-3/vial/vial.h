#ifndef VIAL_H
#define VIAL_H

#include "shell/shell.h"

#include "../cork/cork.h"

void os_init();
void os_main();
void os_keyboard_handler(char key);
void print_banner();

#endif