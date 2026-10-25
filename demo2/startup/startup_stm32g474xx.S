.syntax unified
.cpu cortex-m4
.thumb

.section .isr_vector, "a", %progbits
.balign 1024
.word _estack
.word Reset_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word 0
.word 0
.word 0
.word 0
.word Default_Handler
.word Default_Handler
.word 0
.word Default_Handler
.word SysTick_Handler
.rept 128
.word Default_Handler
.endr

.section .text.Reset_Handler, "ax", %progbits
.global Reset_Handler
.type Reset_Handler, %function
.thumb_func
Reset_Handler:
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
1:
    cmp r1, r2
    bcs 2f
    ldr r3, [r0], #4
    str r3, [r1], #4
    b 1b
2:
    ldr r1, =_sbss
    ldr r2, =_ebss
    movs r3, #0
3:
    cmp r1, r2
    bcs 4f
    str r3, [r1], #4
    b 3b
4:
    bl main
5:
    b 5b
.size Reset_Handler, .-Reset_Handler

.section .text.Default_Handler, "ax", %progbits
.weak Default_Handler
.type Default_Handler, %function
.thumb_func
Default_Handler:
    b Default_Handler
.size Default_Handler, .-Default_Handler
