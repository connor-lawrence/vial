#ifndef IRQS_H
#define IRQS_H

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

void irqs_init();
void setup_irqs();
void enable_interrupts();

struct IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

struct IDTPointer {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


extern struct IDTEntry idt[256];

#endif