gcc -std=gnu99 -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/HELLO_C.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/HELLO_C.C
gcc -std=gnu99 -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/LS.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/LS.C
gcc -std=gnu99 -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/CALC.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/CALC.C