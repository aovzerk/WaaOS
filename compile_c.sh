gcc -std=gnu99 -fpermissive -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/HELLO_C.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/HELLO_C.C
gcc -std=gnu99 -fpermissive -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/LS.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/LS.C
gcc -std=gnu99 -fpermissive -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/CALC.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/CALC.C
gcc -std=gnu99 -fpermissive -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/F_INFO.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/F_INFO.C
gcc -std=gnu99 -fpermissive -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/GUI.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/GUI.C
gcc -std=gnu99 -fpermissive -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/CMD.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/CMD.C
gcc -std=gnu99 -fpermissive -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/POWEROFF.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/POWEROFF.C
gcc -std=gnu99 -fpermissive -Os -I KERNEL -nostdlib -m32 -march=i386 -fno-pie -ffreestanding -o ./C_PROGRAMMS/DRAW_BMP.BIN -Wl,--nmagic,--script=linker.ld ./C_PROGRAMMS/DRAW_BMP.C