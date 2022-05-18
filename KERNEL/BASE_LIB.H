asm(".code16gcc\n"
    "call main\n"
    "int $0x91\n");
static void print(char *string)
{
    asm volatile(
        "push %%cs\n"
        "pop %%ds\n"
        "mov $15, %%bl\n"
        "mov $0x02, %%ah\n"
        "int $0x90\n"
        :
        : "D"(string)
        :
    );
}
static void print_char(char symbol){
    asm volatile(
        "mov $0x13, %%ah\n"
        "int $0x90\n"
        :
        : "a"(symbol)
        :
    );
}
static void exit()
{
    asm (".code16gcc\n"
     "int   $0x91\n");
}
static void load_table_files(char *str){
    asm volatile(

        "push %%cs\n"
        "pop %%es\n"
        "mov $0x12, %%ah\n"
        "int $0x90\n"
        :
        : "b"(str)
        :
    );
}