#include "vial.h"
#include "../cork/cork.h"

void os_init() {
    os_main();
}

void os_main() {
    print_banner();
    while (1) {
        //
    }
}

void os_keyboard_handler(char key) {
    char string[2] = {key, '\0'};
    print(string, VGA_LIGHT_GRAY);
}

void print_banner() {
    print("                              __________      _________\n", VGA_LIGHT_BLUE);
    print("  VialOS Dev ", VGA_LIGHT_BLUE);
    print("with CorK 2.2", VGA_RED);
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