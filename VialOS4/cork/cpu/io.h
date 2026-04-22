#ifndef IO_H
#define IO_H

#include "../cork.h"

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char value);

#endif