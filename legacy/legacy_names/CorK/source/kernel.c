typedef unsigned short two_byte;

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

#define VIDEO_MEMORY ((two_byte*)0xB8000)
static int cursor_location = 0;

void put_character(char c, char color) {
    VIDEO_MEMORY[cursor_location++] = (color << 8) | c;
}

char scancode_to_ascii(uint8_t scancode) {
    static char map[128] = {
        0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
        0,  'a','s','d','f','g','h','j','k','l',';','\'','`',
        0, '\\','z','x','c','v','b','n','m',',','.','/',
    };

    if (scancode < 128)
        return map[scancode];

    return 0;
}

#define KEYBOARD_PORT 0x60

char get_keypress() {
    uint8_t scancode = inb(KEYBOARD_PORT);
    return scancode_to_ascii(scancode);
}

static uint8_t last_scancode = 0;

void keyboard_loop() {
    char green = 0x02;

    while (1) {
        uint8_t scancode = inb(0x60);

        // ignore repeats
        if (scancode == last_scancode) {
            continue;
        }

        last_scancode = scancode;

        char c = scancode_to_ascii(scancode);

        if (c) {
            put_character(c, green);
        }
    }
}

void print(const char *msg, char color) {
    for (int i = 0; msg[i] != '\0'; i++) {
        put_character(msg[i], color);
    }
}

void test_keyboard_input() {
    char c = 'a';  // pretend we pressed 'a'
    put_character(c, 0x07);
}

void cork_main() {
    char green = 0x02;
    print("[CorK/source/kernel.c] Hello, World!", green);
    keyboard_loop();
}
