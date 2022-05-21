./compile_c.sh
fasm BOOT/BOOT.ASM
fasm FILE_SYSTEM/FILE_SYSTEM.ASM
fasm KERNEL/KERNEL.ASM
fasm PROGRAMMS/HELLO_WORLD.ASM
fasm PROGRAMMS/LS.ASM
fasm C_PROGRAMMS/HELLO_C.ASM
fasm C_PROGRAMMS/LS.ASM
fasm C_PROGRAMMS/CALC.ASM
fasm C_PROGRAMMS/F_INFO.ASM
fasm C_PROGRAMMS/GUI.ASM
fasm C_PROGRAMMS/CMD.ASM
fasm TXT/T.ASM
fasm MAKE/OS.ASM OS.IMG

rm ./**/*.BIN

qemu-system-x86_64 -drive file=OS.IMG,index=0,format=raw