

#include "BASE_LIB.H"

void main(void)
{
    print_char('1');
    u_char16 hello[] = "Hello World!\n\r\0";
    u_char16 *ptr = hello;
    print(ptr, 15);
    print(ptr, 15);
    exit();
}