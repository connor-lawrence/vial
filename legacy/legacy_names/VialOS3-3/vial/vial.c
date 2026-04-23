#include "vial.h"

enum Mode {
    OS_TERMINAL_MODE
};

enum Mode os_mode = OS_TERMINAL_MODE;

void os_init() {
    print_banner();
    os_main();
}

void os_main() {
    if (os_mode == OS_TERMINAL_MODE) {
        vsh_main();
    } else {
        print("[ ", VGA_LIGHT_GRAY, 0, 0);
        print("VialOS ", VGA_LIGHT_BLUE, 0, 0);
        print("] Unknown OS mode. Halting with while (1) {}\n", VGA_LIGHT_GRAY, 0, 0);
        while (1) {}
    }
}

void os_keyboard_handler(char key) {
    if (os_mode == OS_TERMINAL_MODE) {
        vsh_keyboard_handler(key);
    } else {
        if (key == '\b') {
            backspace();
        } else {
            char string[2] = {key, '\0'};
            print(string, VGA_LIGHT_GRAY, 0, 0);
        }
    }
}


void print_banner() {
    print("                              __________      _________\n", VGA_LIGHT_BLUE, 0, 0);
    print(" VialOS Dev ", VGA_LIGHT_BLUE, 0, 0);
    print("with CorK 2.2", VGA_RED, 0, 0);
    print("    /   _____  \\    /  _______\\ \n", VGA_LIGHT_BLUE, 0, 0);
    print(" x86-32 - VGA Text Driver", VGA_GREEN, 0, 0);
    print("       \\  \\     \\  \\  /  /\n", VGA_LIGHT_BLUE, 0, 0);
    print("        ___  ___         ___  \\  \\     \\  \\ \\  \\________\n", VGA_LIGHT_BLUE, 0, 0);
    print("___    /  / /__/ _______ \\  \\  \\  \\     \\  \\ \\________   \\ \n", VGA_LIGHT_BLUE, 0, 0);
    print("\\  \\  /  / /  / /  ___  \\ \\  \\  \\  \\     \\  \\          \\  \\ \n", VGA_LIGHT_BLUE, 0, 0);
    print(" \\  \\/  / /  / /  /  /   \\ \\  \\  \\  \\     \\  \\          \\  \\ \n", VGA_LIGHT_BLUE, 0, 0);
    print("  \\    / /  / /  /__/  /  \\ \\  \\  \\  \\_____\\  \\ ________/  /\n", VGA_LIGHT_BLUE, 0, 0);
    print("   \\__/ /__/  \\_______/ \\__\\ \\__\\  \\_________ / \\_________/\n\n", VGA_LIGHT_BLUE, 0, 0);
}