#include "irqs.h"
#include "cork.h"
#include "../drivers/vga.h"

extern void keyboard_isr();

void irqs_init() {
    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] irqs_init() called...\n", VGA_LIGHT_GRAY);

    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] Calling pic_remap()...\n", VGA_LIGHT_GRAY);
    pic_remap();

    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] Calling setup_irqs()...\n", VGA_LIGHT_GRAY);
    setup_irqs();

    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] Calling enable_interrupts()...\n", VGA_LIGHT_GRAY);
    enable_interrupts();
}

void pic_remap() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}

struct IDTEntry idt[256];
struct IDTPointer idt_ptr;

void setup_irqs() {
    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] setup_irqs() called, setting up IRQs...\n", VGA_LIGHT_GRAY);

    unsigned int keyboard_irq_adress = (unsigned int)keyboard_isr;
    idt[33].offset_low = keyboard_irq_adress & 0xFFFF;
    idt[33].offset_high = (keyboard_irq_adress >> 16) & 0xFFFF;
    idt[33].selector = 0x08;
    idt[33].type_attr = 0x8E;
    idt[33].zero = 0;

    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (unsigned int)&idt;
    __asm__ volatile ("lidt %0" : : "m"(idt_ptr));
}

void enable_interrupts() {
    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] enable_interrupts() called, enabling interrupts (\"sti\")...\n", VGA_LIGHT_GRAY);
    __asm__ volatile ("sti");
}