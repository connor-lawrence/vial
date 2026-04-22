section .multiboot
align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

section .text
global start

extern kernel_main

start:
    call kernel_main
    cli

.hang:
    hlt
    jmp .hang

global keyboard_isr

extern handle_keypress

keyboard_isr:
    pusha
    call handle_keypress
    popa
    iret