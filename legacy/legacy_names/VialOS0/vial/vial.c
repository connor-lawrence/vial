#include "vial.h"
#include "../cork/cork.h"

void os_banner() {
    char green = 0x02;
    char blue = 0x09;
    char gray = 0x07;
    char white = 0x0F;
    vga_print(" ___            ___   ___   __   ___           __________     __________       ", blue);
    vga_newline();
    vga_print(" \\  \\          /  /  /  /  /  \\  \\  \\         /   _____  \\   /   _______\\      ", blue);
    vga_newline();
    vga_print("  \\  \\        /  /  /  /  /    \\  \\  \\        \\  \\     \\  \\  \\  \\              ", blue);
    vga_newline();
    vga_print("   \\  \\      /  /  /  /  /  /\\  \\  \\  \\        \\  \\     \\  \\  \\  \\________     ", blue);
    vga_newline();
    vga_print("    \\  \\    /  /  /  /  /  /__\\  \\  \\  \\        \\  \\     \\  \\  \\_________  \\   ", blue);
    vga_newline();
    vga_print("     \\  \\  /  /  /  /  /  ______  \\  \\  \\        \\  \\     \\  \\           \\  \\  ", blue);
    vga_newline();
    vga_print("      \\  \\/  /  /  /  /  /      \\  \\  \\  \\        \\  \\     \\  \\           \\  \\ ", blue);
    vga_newline();
    vga_print("       \\    /  /  /  /  /        \\  \\  \\  \\______  \\  \\_____\\  \\   ________\\  \\", blue);
    vga_newline();
    vga_print("        \\__/  /__/  /__/          \\__\\  \\________\\  \\__________/   \\__________/", blue);
    vga_newline();
}

void os_main() {
    char green = 0x02;
    char blue = 0x09;
    char gray = 0x07;
    char white = 0x0F;
    vga_print("  [", gray);
    vga_print("VialOS/vial/vial.c", blue);
    vga_print("] ", gray);
    vga_print("os_main() ", blue);
    vga_print("called...", gray);
    vga_newline();
    vga_clear();
    os_banner();
}