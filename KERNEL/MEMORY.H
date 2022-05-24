u_char8 *malloc(u_long_int user_size){
    u_long_int MAX = 653312;
    u_long_int size = 0;
    u_char8 *addres = (u_char8 *)0x07E00;
    asm volatile("pusha");
    asm volatile(
        "mov $0x24, %%ah\n"
        "int $0x90\n"
        "mov %%bl, %0\n"
        :"=m"(size)
        : 
        :
    );
    asm volatile("popa");
    size = size * 1024;
    if(size > MAX){
        return addres;
    }
    if(user_size > MAX){
        return addres;
    }
    u_long_int get_memory = MAX - size;
    if(get_memory < user_size){
        return addres;
    }
    addres = size + addres + 1;
    return addres;
}
void save_info_file(u_char8 size){
    asm volatile("pusha");
    asm volatile(
        "mov %0, %%bl\n"
        "mov $0x23, %%ah\n"
        "int $0x90\n"
        :
        : "m"(size)
        :
    );
    asm volatile("popa");
}