FASM.EXE BOOT/BOOT.ASM
FASM.EXE FILE_SYSTEM/FILE_SYSTEM.ASM
FASM.EXE KERNEL/KERNEL.ASM
FASM.EXE MAKE/OS.ASM OS.IMG
qemu-system-x86_64.exe -L "C:\Program Files\qemu" -drive file=OS.img,index=0,if=floppy,format=raw