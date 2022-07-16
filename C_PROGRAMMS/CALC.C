

#include "LIB/BASE_LIB.H"

void main(void)
{
    print((u_char8 *) "Input number1:> ", White);    
    f_string my_str = input();
    print(new_line, Black);
    print((u_char8 *) "Input number2:> ", White);
    f_string my_str2 = input();
    print(new_line, Black);
    print((u_char8 *) "Input operand:> ", White);
    f_string my_op = input();
    print(new_line, Black);
    u_int32 my_num1 = convert_str_to_dec(my_str);
    u_int32 my_num2 = convert_str_to_dec(my_str2);
    
    switch (my_op.data[0])
    {
        case '+':
            my_num1 = my_num1 + my_num2;
            break;
        case '-':
            my_num1 = my_num1 - my_num2;
            break;
        case '*':
            my_num1 = my_num1 * my_num2;
            break;
        case '/':
            my_num1 = my_num1 / my_num2;
            break;
        default:
            break;
    }
    
    f_string my_str3 = convert_dec_to_str(my_num1);
    print((u_char8 *)"Result: ", White);
    print(my_str3.data, White);
}
