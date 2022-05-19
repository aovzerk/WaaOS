

#include "BASE_LIB.H"

void main(void)
{
    print((u_char16 *) "Input number1:> ", White);
    f_string my_str = input();
    print(new_line, Black);
    print((u_char16 *) "Input number2:> ", White);
    f_string my_str2 = input();
    print(new_line, Black);
    u_long_int my_num1 = convert_to_number(my_str);
    u_long_int my_num2 = convert_to_number(my_str2);
    my_num1 = my_num1 + my_num2;
    f_string my_str3 = clear_str(); 
    my_str3 = covert_to_string(my_num1);
    print((u_char16 *)"Result: ", White);
    print(my_str3.data, White);
}
