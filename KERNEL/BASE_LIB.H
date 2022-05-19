#define u_int16 unsigned short int
#define u_char16 unsigned char
#define u_long_int unsigned long int
#define u_long_int64 unsigned long long int
#define White 15
#define Light_Brown 14
#define Light_Magenta 13
#define Light_Red 12
#define Light_Cyan 11
#define Light_Green 10
#define Light_Blue 9
#define Dark_Grey 8
#define Light_Grey 7
#define Brown 6
#define Magenta 5
#define Red 4
#define Cyan 3
#define Green 2
#define Blue 1
#define Black 0
asm(".code16gcc\n"
    "call main\n"
    "int $0x91\n");
u_char16 new_line[] = "\n\r\0";
struct file
{
    u_char16 type;
    u_char16 track;
    u_char16 sector;
    u_char16 num_sectors;
    u_char16 name[12];
};
struct f_string
{
    u_char16 len;
    u_char16 data[255];
};
struct daps
{
    u_char16 p_size = 16;
    u_char16 p_empty = 0;
    u_char16 p_n_setors;
    u_char16 p_empty2 = 0;
    u_int16 p_adres;
    u_int16 p_segment;
    u_long_int64 sector;
};
daps create_daps(u_char16 p_n_setors, u_int16 p_adres, u_long_int64 sector){
    daps new_daps;
    new_daps.p_n_setors = p_n_setors;
    new_daps.p_adres = p_adres;
    new_daps.sector = sector;
    asm (
        "push %%cs\n"
        "pop %%ax\n"
        : "=a"(new_daps.p_segment)
        :
        :
    );
    return new_daps;
}
f_string clear_str(){
    f_string str;
    for(u_int16 i = 0; i < 255; i++){
        str.data[i] = 0;
    }
    return str;
}
f_string calc_len(f_string str){
    for(u_int16 i = 0; i < 255; i++){
        if(str.data[i] == 0){ 
            
            str.len = i;
            break;
        }
    }
    return str;
}
void Reverse(u_char16* begin, u_char16* end, u_char16 n)
{
    if (n > 1)
    {
        u_char16 t = *begin;
        *begin = *end;
        *end = t;
        Reverse(begin + 1, end - 1, n - 2);
    }
}
f_string covert_to_string(u_long_int num){
    f_string new_str = clear_str();
    u_int16 i = 0;
    for(; i < 255; i++){
        if(num / 10 == 0 && num % 10 == 0) break;
        u_int16 tmp = num % 10;
        num = num / 10;
        new_str.data[i] = tmp + 0x30;
        
    }
    Reverse(new_str.data,  new_str.data + i - 1, i);
    new_str.data[i] = 0;
    new_str = calc_len(new_str);
    return new_str;
}
u_long_int convert_to_number(f_string str){
    u_long_int num = 0;
    for(u_int16 i = 0; i < 255; i++){
        if(str.data[i] == 0) break;
        num = (num + (str.data[i] - 0x30)) * 10;
    }
    return num / 10;
}
void print(u_char16 *string, u_char16 color)
{
    asm volatile("pusha");
    asm volatile(
        "push %%cs\n"
        "pop %%ds\n"
        "mov $0x02, %%ah\n"
        "int $0x90\n"
        :
        : "D"(string), "b"(color)
        :
    );
    asm volatile("popa");
}
void print_nl(u_char16 *string, u_char16 color){
    print(string, color);
    print(new_line, Black);
}
void print_char(u_char16 symbol){
    asm volatile("pusha");
    asm volatile(
        "mov $0x13, %%ah\n"
        "int $0x90\n"
        :
        : "a"(symbol)
        :
    );
    asm volatile("popa");
}
void exit()
{
    asm (".code16gcc\n"
     "int   $0x91\n");
}
void load_table_files(file *files){
    asm volatile("pusha");
    asm volatile(

        "push %%cs\n"
        "pop %%es\n"
        "mov $0x12, %%ah\n"
        "int $0x90\n"
        :
        : "b"(files)
        :
    );
    asm volatile("popa");
}
f_string input(){
    f_string my_str = clear_str();
    asm volatile("pusha");
    asm volatile(

        "push %%cs\n"
        "pop %%es\n"
        "mov $0x3, %%ah\n"
        "int $0x90\n"
        :
        : "c"(254),"D"(my_str.data)
        :
    );
    asm volatile("popa");
    my_str = calc_len(my_str);
    return my_str;
}
u_char16 load_daps(daps *new_daps){
    u_char16 status = 0;
    asm volatile("pusha");
    asm volatile(

        "push %%cs\n"
        "pop %%ds\n"
        "mov $0x16, %%ah\n"
        "int $0x90\n"
        : "=a"(status)
        : "S"(new_daps)
        :
    );
    asm volatile("popa");
    return status;
}