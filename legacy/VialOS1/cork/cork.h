#ifndef CORK_H
#define CORK_H

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

void kernel_main();
void print(const char* string, uint16_t color);
void handle_keypress();

#endif