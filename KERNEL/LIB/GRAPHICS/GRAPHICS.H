#ifndef u_char8
#define u_char8 unsigned char
#define u_short16 unsigned short int
#define u_int32 unsigned long int
#define u_long_int64 unsigned long long int
#endif
void set_video_mode(u_char8 mode){
    asm volatile("pusha");
    asm volatile(
        "int $0x10\n"
        :
        :"a"(mode)
        :
    );
    asm volatile("popa");
}

//      !!! NOT WORK !!!
u_char8 get_video_mode(){
    u_char8 mode = 3;
    asm volatile("pusha");
    asm volatile(
        "mov $0x0f, %%ah\n"
        "int $0x10\n"
        :"=a"(mode)
        :
        :
    );
    asm volatile("popa");
    return mode;
}