
asm (".code16gcc\n"
     "call  dosmain\n"
     "int   $0x91\n");
static void print(char string[])
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

int dosmain(void)
{
    print("Hello, World!");
    return 0;
}