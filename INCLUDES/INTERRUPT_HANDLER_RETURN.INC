INTERRUPT_HANDLER_RETURN:
    pop ax
    pop bx
    pop cx
    xor ax,ax
    xor bx,bx
    xor cx,cx
    jmp RETURN_INT
iret