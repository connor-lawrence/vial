#include "vial.h"
#include "../cork/cork.h"

void os_init() {
    os_main();
}

void os_main() {
    print("[ ", VGA_LIGHT_GRAY);
    print("VialOS ", VGA_LIGHT_BLUE);
    print("] OS fully initialized, printing banner...\n", VGA_LIGHT_GRAY);
    
    print_banner();
}

void print_banner() {
    print("                              __________      _________\n", VGA_LIGHT_BLUE);
    print("  VialOS 2.1 ", VGA_LIGHT_BLUE);
    print("with CorK 2.1", VGA_RED);
    print("   /   _____  \\    /  _______\\ \n", VGA_LIGHT_BLUE);
    print("  x86 - VGA Text Driver", VGA_GREEN);
    print("      \\  \\     \\  \\  /  /\n", VGA_LIGHT_BLUE);
    print("        ___  ___         ___  \\  \\     \\  \\ \\  \\________\n", VGA_LIGHT_BLUE);
    print("___    /  / /__/ _______ \\  \\  \\  \\     \\  \\ \\________   \\ \n", VGA_LIGHT_BLUE);
    print("\\  \\  /  / /  / /  ___  \\ \\  \\  \\  \\     \\  \\          \\  \\ \n", VGA_LIGHT_BLUE);
    print(" \\  \\/  / /  / /  /  /   \\ \\  \\  \\  \\     \\  \\          \\  \\ \n", VGA_LIGHT_BLUE);
    print("  \\    / /  / /  /__/  /  \\ \\  \\  \\  \\_____\\  \\ ________/  /\n", VGA_LIGHT_BLUE);
    print("   \\__/ /__/  \\_______/ \\__\\ \\__\\  \\_________ / \\_________/\n\n", VGA_LIGHT_BLUE);
}