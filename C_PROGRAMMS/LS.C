
#include "BASE_LIB.H"

char my_table[512];
void main(){

    
    for(int i = 0; i < 512; i++){
        my_table[i] = 0;
    }
    print("LS Programm v0.1 KIM\n\r\0");
    
    load_table_files(my_table);
    int i = 4;
    while (i < 512)
    {
        print(my_table + i);
        i = i + 16;
    }
    exit();
}
