

#include "BASE_LIB.H"

void main(void)
{
    u_char16 my_text[512];
    daps my_daps = create_daps(1, (u_int16) my_text, 27);
    u_char16 st = load_daps(&my_daps);
    f_string mt_str = covert_to_string(st);
    print_nl(my_text, White);
}