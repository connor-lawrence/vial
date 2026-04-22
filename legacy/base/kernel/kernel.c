void kmain() {
    char *video = (char*) 0xB8000;

    char *msg = "[CorK] Hello, World!";

    for (int i = 0; msg[i] != '\0'; i++) {
        video[i * 2] = msg[i];
        video[i * 2 + 1] = 0x07;
    }
}