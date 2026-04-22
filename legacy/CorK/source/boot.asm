section .multiboot
align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

section .text
global start

extern cork_main

start:
    call cork_main
    cli
    
.hang:
    hlt
    jmp .hang
