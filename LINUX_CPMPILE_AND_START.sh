fasm BOOT/BOOT.ASM
fasm FILE_SYSTEM/FILE_SYSTEM.ASM
fasm KERNEL/KERNEL.ASM
fasm PROGRAMMS/HELLO_WORLD.ASM
fasm PROGRAMMS/LS.ASM
fasm PROGRAMMS/GUI.ASM
fasm PROGRAMMS/HELLO2.ASM
fasm MAKE/OS.ASM OS.IMG
./compile_c.sh
rm ./BOOT/BOOT.BIN
rm ./FILE_SYSTEM/FILE_SYSTEM.BIN
rm ./KERNEL/KERNEL.BIN
rm ./PROGRAMMS/HELLO_WORLD.BIN
rm ./PROGRAMMS/LS.BIN
rm ./PROGRAMMS/GUI.BIN
rm ./C_PROGRAMMS/HELLO_C.BIN
qemu-system-x86_64 -drive file=OS.IMG,index=0,if=floppy,format=raw