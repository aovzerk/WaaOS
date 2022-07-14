#ifndef u_char8
#define u_char8 unsigned char
#define u_int16 unsigned short int
#define u_long_int unsigned long int
#define u_long_int64 unsigned long long int
#endif

struct vbeInfoBlock {
    u_char8 vbeSignature[4];             // == "VESA"
    u_int16 vbeVersion;                 // == 0x0300 for VBE 3.0
    u_int16 oemStringPtr[2];            // isa vbeFarPtr
    u_char8 capabilities[4];
    u_int16 videoModePtr[2];         // isa vbeFarPtr
    u_int16 totalMemory;             // as # of 64KB blocks
};

vbeInfoBlock vbeInfoGet(){
    vbeInfoBlock info;
    asm volatile("pusha");
    asm volatile(
        "mov $0x4f00, %%ax\n"
        "push %%cs\n"
        "pop %%es\n"
        "int $0x10\n"
        :
        :"D"(&info)
        :
    );
    asm volatile("popa");
    return info;
}