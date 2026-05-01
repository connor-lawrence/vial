#ifndef TYPES_H
#define TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;

typedef u32 uintptr_t;
typedef i32 intptr_t;

typedef u32 size_t;

#define bool u8
#define true 1
#define false 0

#define NULL ((void*)0)

typedef u32 phys_addr_t;
typedef u32 virt_addr_t;

typedef u8 byte;
typedef u16 word;
typedef u32 dword;

#endif