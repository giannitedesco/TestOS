global environment
environment:
    mov esp, stack_top
    extern kernel_main
    call kernel_main    
    cli
    .hang: hlt
    jmp .hang

section .bss
align 4
stack_bottom:
resb 16384
stack_top:

section .text
resb 16384


