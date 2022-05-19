

#include "BASE_LIB.H"

void main(void)
{
    print_char('1');
    u_char8 hello[] = "Hello World!\n\r\0";
    u_char8 *ptr = hello;
    print(ptr, 15);
    print(ptr, 15);
    exit();
}