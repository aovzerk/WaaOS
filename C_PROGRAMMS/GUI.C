

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
    
}
void print_selected(file *files, u_char8 selected){
    u_char8 select[] = "-> ";
    u_char8 empty[] = "                ";
    for(u_char8 i = 0; i < 32; i++){
        if(files[i].name[0] != 0){
            set_cursor(2 + i, 2);
            print(empty, Black);
            if(i == selected){
                set_cursor(2 + i, 2);
                print(select, White);
                print(files[i].name, White);
            }else {
                set_cursor(2 + i, 5);
                print(files[i].name, White);
            }
            
        }
    }
}
void clear_info(){
    u_char8 empty[] = "                          ";
    for(u_char8 i = 2; i < 10; i++){
        set_cursor(i, 30);
        print(empty, Black);
    }
}
void print_info_file(file *files, u_char8 selected){
    clear_info();
    set_cursor(2, 30);
    u_char8 file_data[512];
    daps daps_file = get_r_daps_file(files[selected].name, (u_int16) file_data);
    daps_file.p_n_setors = 1;
    f_string num_sectors = convert_to_string(daps_file.p_n_setors);
    f_string first_sector = convert_to_string(daps_file.sector);
    print((u_char8 *) "File: ", Light_Grey);
    print(files[selected].name, Light_Grey);
    set_cursor(3, 30);
    print((u_char8 *) "Num. Sectors: ", Light_Grey);
    print(num_sectors.data, Light_Grey);
    set_cursor(4, 30);
    print((u_char8 *) "First Sector: ", Light_Grey);
    print(first_sector.data, Light_Grey);
    set_cursor(5, 30);
    if(daps_file.data_file.type == 1){
        print((u_char8 *) "Type: execute", Red);
    } else if(daps_file.data_file.type == 2){
        load_daps(&daps_file);
        print((u_char8 *) "Type: text", Green);
        set_cursor(6, 30);
        print((u_char8 *) "first 512 byte of file:", Light_Grey);
        set_cursor(7, 30);
        print((u_char8 *) "=========================", Red);
        set_cursor(8, 30);
        print(file_data, Light_Grey);
        set_cursor(9, 30);
        print((u_char8 *) "=========================", Red);
        
    }else if(daps_file.data_file.type == 3){
        daps_file.p_n_setors = 1;
        load_daps(&daps_file);
        print_nl((u_char8 *) "Type: image", Cyan);
    }
}
u_char8 get_files_len(file *files){
    for(u_char8 i = 0; i < 32; i++){
        print_char(i+0x30);
        if(files[i].name[0] == 0){
            return i;
        }
    }
}
void main(void)
{
    print_border();
    file my_files[32];
    u_char8 selected_file = 0;
    load_table_files(my_files);
    u_char8 num_files = get_files_len(my_files);
    print_selected(my_files, selected_file);
    print_info_file(my_files, selected_file);
    while (true)
    {
        set_cursor(25, 0);
        u_char8 my_char = get_scan_code_key();
        
        if(my_char == 0x50){
            if(selected_file < num_files - 1) selected_file++;
        } else if(my_char == 0x48){
            if(selected_file != 0) selected_file--;
        }else if(my_char == 28){
            if(my_files[selected_file].type == 1){
                daps daps_file = get_r_daps_file(my_files[selected_file].name, (u_int16) 0x07E00);
                clear_Screen();
                start_programm(&daps_file, 0);
            } else if(my_files[selected_file].type == 3){
                daps daps_file = get_r_daps_file((u_char8 *)"d_bmp", (u_int16) 0x07E00);
                clear_Screen();
                u_char8 args_for_d_bmp[40] = "d_bmp";
                args_for_d_bmp[5] == 0;
                for(u_char8 i = 6; i < 18; i++){
                    args_for_d_bmp[i] = my_files[selected_file].name[i - 6];
                }
                start_programm(&daps_file, args_for_d_bmp);
            }
        }
        print_selected(my_files, selected_file);
        print_info_file(my_files, selected_file);
    }
        
}