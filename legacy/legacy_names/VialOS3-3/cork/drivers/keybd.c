#include "keybd.h"
#include "../cork.h"

static uint8_t last_scancode = 0;

void keyboard_init() {}

void keyboard_poll() {
    uint8_t scancode = inb(0x60);
    if (scancode == last_scancode) return;
    last_scancode = scancode;
    if (scancode & 0x80) {
        // Release
    } else {
        char key = scancode_to_ascii[scancode];
        if (key) {
            keyboard_handler(key);
        }
    }

}