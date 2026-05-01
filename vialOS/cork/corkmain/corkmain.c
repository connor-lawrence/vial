#include "corkmain.h"
#include "types.h"
#include "../../vial/vialmain/vialmain.h"

void kernel_init() {
    os_init();
    kernel_main_loop();
}

void kernel_main_loop() {
    while (1) {
        os_main_loop();
    }
}