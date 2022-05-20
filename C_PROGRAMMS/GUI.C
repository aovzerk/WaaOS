

#include "BASE_LIB.H"
void print_wall(u_char8 x, u_char8 y){
    set_cursor(x, y);
    u_char8 hello = '-';
    for(u_char8 i = y; i < 79; i++){
        print_char(hello);
        set_cursor(x, i);
    }
}
void print_wall2(u_char8 x, u_char8 y){
    set_cursor(x, y);
    u_char8 hello = '|';
    for(u_char8 i = x; i < 23; i++){
        print_char(hello);
        set_cursor(i, y);
    }
}
void print_border(){
    clear_Screen();
    print_wall(0,0);
    print_wall2(1,0);
    print_wall(22, 0);
    print_wall2(1,77);
    print_wall2(1, 25);
    set_cursor(25,0);
}
void main(void)
{
    print_border();
    file my_files[32];
    u_char8 base_position = 0;
    load_table_files(my_files);
    set_cursor(2, 5);
    print(my_files[0].name, White);
    while(true){}
}