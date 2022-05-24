

#include "BASE_LIB.H"
#include "MEMORY.H"
void clear_str_file_name(u_char8 *str, u_char8 len){
    for(u_int16 i = 0; i < len; i++){
        str[i] = 0;
    }
}

void main(void)
{
    u_char8 user[] = "user:>";
    u_char8 not_found[] = "Command not found :(";
    while (true)
    {
        print(new_line, Black);
        print(user, White);
        f_string user_guffer = input();
        for(u_char8 i =0 ; i < 254; i++){
            if(user_guffer.data[i] == ' '){
                user_guffer.data[i] = 0;
            }
        }
        u_char8 file_name[13];
        clear_str_file_name(file_name, 13);
        for(u_char8 i = 0; i < 13; i++){
            if(user_guffer.data[i] == 0) break;
            if(user_guffer.data[i] == ' ') break;
            file_name[i] = user_guffer.data[i];
        }
        if(file_name[0] != ' ' && file_name[0] != 0){
            daps daps_file = get_r_daps_file(file_name, (u_int16) 0x07E00);
            print(new_line, Black);
            if(daps_file.p_empty != 1){
                save_info_file(daps_file.data_file.num_clusters);
                start_programm(&daps_file, user_guffer.data);
            } else {
                print(not_found, Red);
            }
        }
    }
}