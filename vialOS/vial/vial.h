#ifndef VIAL_H
#define VIAL_H

typedef enum {
    OS_MODE_INIT,
    OS_MODE_VSH,
    OS_MODE_TEST
} OSMode;

extern OSMode os_mode;

void os_init();
void os_main_loop();

#endif