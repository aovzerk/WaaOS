org 7E00h
GLOBAL:
jmp START_K
;-----------------------------------------------------------
    include 'INCLUDES\MACROS.INC'
    include 'INCLUDES\BASE_FUNCTIONS.INC'
    include 'INCLUDES\INTERRUPT_HANDLER_RETURN.INC'
    include 'INCLUDES\MAIN_INTERRUPT_HANDLER.INC'
    include 'INCLUDES\CONST.INC'
;-----------------------------------------------------------
START_K:
SET_INTERRUPT_HANDLER 90H,MAIN_INTERRUPT_HANDLER
SET_INTERRUPT_HANDLER 91H,INTERRUPT_HANDLER_RETURN
MAIN:
PRINTSF HELLO_WORLD, BLACK

jmp $

RETURN_INT:

;сюда передает управление int 91h

jmp $

jmp MAIN
PRINTSF HELLO_WORLD, BLACK
JMP $
HELLO_WORLD: stringf "Hello world!"
CALC_SIZE SIZE_KERNEL, GLOBAL