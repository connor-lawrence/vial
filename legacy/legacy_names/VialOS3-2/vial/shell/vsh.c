#include "vsh.h"
#include "../vial.h"

char input_buffer[256];
int input_buffer_index = 0;

void vsh_main() {
    clear_line();
    print("vsh> ", VGA_GREEN, 0);
    print(input_buffer, VGA_GREEN, 1);
}

void vsh_keyboard_handler(char key) {
    if (key == '\b') {
        backspace();
        if (input_buffer_index > 0) {
            input_buffer_index--;
        }
    } else if (key == '\n') {
        print("\n", VGA_GREEN, 0);
        input_buffer[input_buffer_index] = '\0';
        vsh_execute_command(input_buffer);
        input_buffer_index = 0;
    } else {
        input_buffer[input_buffer_index++] = key;
    }
}

void vsh_execute_command(const char* command) {
    
}