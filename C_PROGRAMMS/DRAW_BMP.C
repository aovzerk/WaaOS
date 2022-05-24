

#include "BASE_LIB.H"
#include "GRAPHICS.H"

u_char8 data_file[51200];
void main(u_char8 *args)
{
    
    u_char8 my_args[255] = "1";
    copy_data(my_args, args, 254);
    daps my_daps = get_r_daps_file(my_args + 6, (u_int16)data_file);
    if(my_daps.p_empty == 1 || my_daps.data_file.type != 3 || my_args[6] == 0){
        print(new_line, Black);
        print((u_char8 *)"FILE NOT FOUND OR INVALID TYPE", Red);
    }else {
        load_daps(&my_daps);
        set_video(0x10);
        draw_image_bmp(data_file, 100,110);
        u_char8 exit[] = "1";
        input_no_format(exit, 1);
        set_video(3);
    }
}