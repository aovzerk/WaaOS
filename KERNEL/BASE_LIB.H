#define u_int16 unsigned short int
#define u_char16 unsigned char
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
struct file
{
    u_char16 type;
    u_char16 track;
    u_char16 sector;
    u_char16 num_sectors;
    u_char16 name[12];
};
static void print(u_char16 *string, u_char16 color)
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
    u_char16 new_line[] = "\n\r\0";
    print(string, color);
    print(new_line, Black);
}
static void print_char(u_char16 symbol){
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
static void exit()
{
    asm (".code16gcc\n"
     "int   $0x91\n");
}
static void load_table_files(file *files){
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