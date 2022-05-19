

#include "BASE_LIB.H"

void main(void)
{   
    u_char16 my_text[512];
    u_char16 file_name[] = "txt";
    daps my_daps = get_r_daps_file(file_name, (u_int16) my_text);
    load_daps(&my_daps);
    print(my_text, White);
}