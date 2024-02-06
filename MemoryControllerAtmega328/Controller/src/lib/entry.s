    .section .text
    .globl entry_point
    .type entry_point, @function
entry_point:
    call 0x1C00
    ret

    .section .bootloader
boot:
    jmp boot
