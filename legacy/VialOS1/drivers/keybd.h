#ifndef KEYBOARD_H
#define KEYBOARD_H

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char value);

#endif