#define u_int16 unsigned short int
#define u_char8 unsigned char
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
u_char8 new_line[] = "\n\r\0";

struct file
{
    u_char8 type;
    u_char8 empty;
    u_char8 num_sectors;
    u_char8 sector;
    u_char8 name[12];
};
struct daps
{
    u_char8 p_size = 16;
    u_char8 p_empty = 0;
    u_char8 p_n_setors;
    u_char8 p_empty2 = 0;
    u_int16 p_adres;
    u_int16 p_segment;
    u_long_int64 sector;
    file data_file;
};
struct f_string
{
    u_char8 len;
    u_char8 data[255];
};
daps create_daps(u_char8 p_n_setors, u_int16 p_adres, u_long_int64 sector){
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
void Reverse(u_char8* begin, u_char8* end, u_char8 n)
{
    if (n > 1)
    {
        u_char8 t = *begin;
        *begin = *end;
        *end = t;
        Reverse(begin + 1, end - 1, n - 2);
    }
}
f_string convert_to_string(u_long_int num){
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
void print(u_char8 *string, u_char8 color)
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
void print_nl(u_char8 *string, u_char8 color){
    print(string, color);
    print(new_line, Black);
}
void print_char(u_char8 symbol){
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
void input_no_format(u_char8 *str, u_int16 len){
    asm volatile("pusha");
    asm volatile(

        "push %%cs\n"
        "pop %%es\n"
        "mov $0x3, %%ah\n"
        "int $0x90\n"
        :
        : "c"(len),"D"(str)
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
u_char8 load_daps(daps *new_daps){
    u_char8 status = 0;
    asm volatile("pusha");
    asm volatile(

        "push %%cs\n"
        "pop %%ds\n"
        "mov $0x17, %%ah\n"
        "int $0x90\n"
        : "=a"(status)
        : "S"(new_daps)
        :
    );
    asm volatile("popa");
    return status;
}
u_char8 save_daps(daps *new_daps){
    u_char8 status = 0;
    asm volatile("pusha");
    asm volatile(
        "push %%cs\n"
        "pop %%ds\n"
        "mov $0x18, %%ah\n"
        "int $0x90\n"
        : "=a"(status)
        : "S"(new_daps)
        :
    );
    asm volatile("popa");
    return status;
}
u_char8 get_len_str(u_char8 *str){
    for(u_char8 i = 0; i < 255; i++){
        if(str[i] == 0) return i;
    }
}
u_char8 cmpstr(u_char8 *str1, u_char8 *str2){
    u_char8 len_str1 = get_len_str(str1);
    u_char8 len_str2 = get_len_str(str2);
    if(len_str1 != len_str2) return 1;
    for(u_char8 i = 0; i < len_str1; i++){
        if(str1[i] != str2[i]) return 1;
    }
    return 0;
}
daps get_r_daps_file(u_char8 *str, u_int16 p_adres){
    file my_files[32];
    load_table_files(my_files);
    daps new_daps;
    for(u_char8 f = 0; f < 32; f++){
        if(cmpstr(str, my_files[f].name) == 0){
            new_daps = create_daps( my_files[f].num_sectors, p_adres, my_files[f].sector);
            new_daps.data_file = my_files[f];
            return new_daps;
        }
    }
    new_daps.p_empty = 1;
    return new_daps;
}
void start_programm(daps *new_daps, u_char8 *args){
    asm volatile(
        "push %%cs\n"
        "pop %%ds\n"
        "mov $0x19, %%ah\n"
        "int $0x90\n"
        :
        :"S"(new_daps),"b"(args)
        :
    );
}
u_char8 get_scan_code_key(){
    u_char8 new_char = 0;
    asm volatile("pusha");
    asm volatile(
        "xor %%ax,%%ax\n"
        "int $0x16\n"
        "movb %%ah, %0\n"
        :
        :"m"(new_char)
        :
    );
    asm volatile("popa");
    return new_char;
}
void set_cursor(u_char8 x, u_char8 y){
    asm volatile("pusha");
    asm volatile(
        "mov $0x4, %%ah\n"
        "mov %0, %%dh\n"
        "mov %1, %%dl\n"
        "int $0x90\n"
        :
        :"r"(x), "r"(y)
        :
    );
    asm volatile("popa");
}
void clear_Screen(){
    asm volatile("pusha");
    asm volatile(
        "int $0x90\n"
        :
        :"a"(3)
        :
    );
    asm volatile("popa");
}
void copy_data(u_char8 *str1, u_char8 *str2,u_char8 len){
    asm volatile("pusha");
    asm volatile(
        "mov $0x20, %%ah\n"
        "int $0x90\n"
        : 
        : "b"(str2),"D"(str1),"c"(len)
        :
    );
    asm volatile("popa");
}
void power_off(){
    asm volatile(
        "mov $0x21, %%ah\n"
        "int $0x90\n"
        : 
        :
        :
    );
}