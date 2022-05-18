

#include "BASE_LIB.H"

void main(void)
{
    print_char('1');
    char hello[] = "Hello World!\n\r\0";
    char *ptr = hello;
    print(ptr);
    print(ptr);
    exit();
}