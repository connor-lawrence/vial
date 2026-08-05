#pragma once
#include "types.h"

void debug_putc(char c);
void debug_print(const char *str);
void debug_print_int(const char *before, const u64 x, const char *after);
void debug_print_hex(const char *before, const u64 x, const char *after);
