#ifndef CORK_H
#define CORK_H

#include "cpu/cpu.h"
#include "drivers/drivers.h"

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

void kernel_init();
void kernel_main_loop();

#endif