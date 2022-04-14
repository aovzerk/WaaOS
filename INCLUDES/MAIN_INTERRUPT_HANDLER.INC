MAIN_INTERRUPT_HANDLER:


cmp ah,0;al=видеорежим
je HF_SET_VIDEO

cmp ah,1;ds:di-str,bl-color
je HF_PRINTSF


HF_SET_VIDEO:
    call F_SET_VIDEO
iret

HF_PRINTSF:
    call F_PRINTSF
iret