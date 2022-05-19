
#include "BASE_LIB.H"

void main(){
    file my_files[32];
    load_table_files(my_files);
    u_char16 empty_string[] = "\0";
    u_char16 my_string[] = "LS Programm v0.1 KIM\n\r\0";
    u_char16 lines[] = "=====================\n\r\0";
    print(my_string, Light_Blue);
    print_nl(empty_string, Black);
    print(lines, White);
    u_int16 size = sizeof(my_files) / sizeof(my_files[0]);
    for(u_char16 f = 0; f < size; f++){
        if(my_files[f].name[0] == 0) break;
        print_nl(my_files[f].name, Light_Grey);
    }
    print(lines, White);
}

