

#include "BASE_LIB.H"
#include "GRAPHICS.H"
void print_wall(u_char8 x, u_char8 y){
    set_cursor(x, y);
    u_char8 hello = '-';
    for(u_char8 i = y; i < 81; i++){
        print_char(hello, Light_Grey);
        set_cursor(x, i);
    }
}
void print_wall2(u_char8 x, u_char8 y){
    set_cursor(x, y);
    u_char8 hello = '|';
    for(u_char8 i = x; i < 30; i++){
        print_char(hello, Light_Grey);
        set_cursor(i, y);
    }
}
void print_wall3(u_char8 x, u_char8 y){
    set_cursor(x, y);
    u_char8 hello = '-';
    for(u_char8 i = y; i < 5 + y; i++){
        print_char(hello, Light_Grey);
        set_cursor(x, i);
    }
}
void print_border(){
    print_wall(0,0);
    print_wall2(1,0);
    print_wall(29, 0);
    print_wall2(1,79);
    print_wall2(1, 25);
    print_wall3(4, 26);
    
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
void clear_info(){   //------------------------------------------------------
    u_char8 empty[] = "                                                     ";
    for(u_char8 i = 2; i < 17; i++){
        set_cursor(i, 26);
        print(empty, Black);
    }
}
u_char8 file_data[51200];
// u_char8 file_data_bmp[51200];
void print_info_file(file *files, u_char8 selected){
    clear_info();
    set_cursor(2, 28);
    daps daps_file = get_r_daps_file(files[selected].name, (u_int16) file_data);
    f_string num_sectors = convert_to_string(daps_file.p_n_sectors);
    f_string first_sector = convert_to_string(daps_file.sector);
    print((u_char8 *) "File: ", Light_Grey);
    print(files[selected].name, Light_Grey);
    set_cursor(2, 60);
    print((u_char8 *) "Num. Sector:  ", Light_Grey);
    print(num_sectors.data, Light_Grey);
    set_cursor(3, 60);
    print((u_char8 *) "First Sector: ", Light_Grey);
    print(first_sector.data, Light_Grey);
    set_cursor(5, 26);
    print((u_char8 *) "-----------------------------------------------------", Light_Grey);
    set_cursor(3, 28);
    print((u_char8 *) "Type: ", Light_Grey);
    if(daps_file.data_file.type == 1){
        print((u_char8 *) "execute", Red);
    } else if(daps_file.data_file.type == 2){
        print((u_char8 *) "text", Green);
        daps_file.p_n_sectors = 1;
        load_daps(&daps_file);
        set_cursor(7, 28);
        print((u_char8 *) "first 512 byte of file:", Light_Grey);
        set_cursor(8, 28);
        print((u_char8 *) "=========================", Red);
        set_cursor(9, 28);
        print(file_data, Light_Grey);
        set_cursor(10, 28);
        print((u_char8 *) "=========================", Red);
        
    }else if(daps_file.data_file.type == 3){
        print((u_char8 *) "image", Cyan);
        u_char8 n_sectors = daps_file.p_n_sectors;
        daps_file.p_n_sectors = 1;
        load_daps(&daps_file);
        u_int16 w;
        u_int16 h;
        get_res_image(file_data, &w, &h);
        set_cursor(6, 30);
        print((u_char8 *)"res:     x    ",Light_Grey);
        set_cursor(6, 35);
        print(convert_to_string(w).data,Light_Grey);
        set_cursor(6, 41);
        print(convert_to_string(h).data,Light_Grey);
        if(w * h <= 16384){
            daps_file.p_n_sectors = n_sectors;
            load_daps(&daps_file);
            draw_image_bmp(file_data, 250, 130);
        }
    }
}
u_char8 get_files_len(file *files){
    for(u_char8 i = 0; i < 64; i++){
        if(files[i].name[0] == 0){
            return i;
        }
    }
}
void main(void)
{
    set_video(0x12);
    print_border();
    file my_files[64];
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