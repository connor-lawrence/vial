#include "vial.h"
#include "../cork/cork.h"
#include "../drivers/vga.h"

OSMode mode = HOME;

void os_main() {
    print("  [ ", VGA_LIGHT_GRAY);
    print("VialOS ", VGA_LIGHT_BLUE);
    print("] os_main() called, OSMode = HOME, calling print_banner()...\n", VGA_LIGHT_GRAY);
    print_banner();
}

void print_banner() {
    print("  [ ", VGA_LIGHT_GRAY);
    print("VialOS ", VGA_LIGHT_BLUE);
    print("] print_banner() called, printing banner...\n", VGA_LIGHT_GRAY);

    print("                                __________      _________\n", VGA_LIGHT_BLUE);
    print("  VialOS 1.1 ", VGA_LIGHT_BLUE);
    print("with CorK 1.1", VGA_RED);
    print("     /   _____  \\    /  _______\\ \n", VGA_LIGHT_BLUE);
    print("  x86 - VGA Text Driver", VGA_GREEN);
    print("        \\  \\     \\  \\  /  /\n", VGA_LIGHT_BLUE);
    print("          ___  ___         ___  \\  \\     \\  \\ \\  \\________\n", VGA_LIGHT_BLUE);
    print("  ___    /  / /__/ _______ \\  \\  \\  \\     \\  \\ \\________   \\ \n", VGA_LIGHT_BLUE);
    print("  \\  \\  /  / /  / /  ___  \\ \\  \\  \\  \\     \\  \\          \\  \\ \n", VGA_LIGHT_BLUE);
    print("   \\  \\/  / /  / /  /  /   \\ \\  \\  \\  \\     \\  \\          \\  \\ \n", VGA_LIGHT_BLUE);
    print("    \\    / /  / /  /__/  /  \\ \\  \\  \\  \\_____\\  \\ ________/  /\n", VGA_LIGHT_BLUE);
    print("     \\__/ /__/  \\_______/ \\__\\ \\__\\  \\_________ / \\_________/\n\n", VGA_LIGHT_BLUE);
}