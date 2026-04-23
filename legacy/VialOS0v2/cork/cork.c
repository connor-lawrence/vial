#include "cork.h"
#include "io.h"
#include "irqs.h"
#include "../drivers/keybd.h"
#include "../drivers/vga.h"
#include "../vial/vial.h"

extern void keyboard_isr();

void kernel_main() {

    vga_init();
    print("\n  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] kernel_main and vga_init() called...\n", VGA_LIGHT_GRAY);
    
    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] Calling irqs_init()...\n", VGA_LIGHT_GRAY);
    irqs_init();

    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] Calling os_main()...\n", VGA_LIGHT_GRAY);
    os_main();
}

void print(const char* string, uint16_t color) {
    vga_print(string, color);
}

void handle_keypress() {
    print("  [ ", VGA_LIGHT_GRAY);
    print("CorK ", VGA_RED);
    print("] handle_keypress()", VGA_LIGHT_GRAY);

}