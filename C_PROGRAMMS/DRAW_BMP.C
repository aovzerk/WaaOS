

#include "BASE_LIB.H"
u_char8 get_pixel_color(u_char8 *data_img){
    u_char8 pixel = 0;
    asm volatile("pusha");
    asm volatile(
        "mov $0x22, %%ah\n"
        "int $0x90\n"
        "mov %%al, %0\n"
        :"=m"(pixel)
        :"S"(data_img)
        :
    );
    asm volatile("popa");
    return pixel;
}
void print_pixel(u_char8 pixel, u_char8 x, u_char8 y){
    asm volatile("pusha");
    asm volatile(
        "mov $0x0C, %%ah\n"
        "xor %%bx,%%bx\n"
        "mov %0, %%al\n"
        "int $0x10\n"
        :
        :"m"(pixel),"d"(x),"c"(y)
        :
    );
    asm volatile("popa");
}
void main(u_char8 *args)
{
    u_char8 my_args[255] = "1";
    copy_data(my_args, args, 254);
    u_char8 data_file[4608];
    u_char8 *data_img = data_file + 138;//42;//+3
    daps my_daps = get_r_daps_file(my_args+6, (u_int16)data_file);
    if(my_daps.p_empty == 1 || my_daps.data_file.type != 3 || my_args[6] == 0){
        print(new_line, Black);
        print((u_char8 *)"FILE NOT FOUND OR INVALID TYPE", Red);
    }else {
        load_daps(&my_daps);
        set_video(0x12);
        u_char8 pixel_color = get_pixel_color(data_img);
        u_char8 w = data_file[18];
        u_char8 h = data_file[22];
        u_char8 x = h;
        u_char8 y = 1;
        for(u_char8 i = 0; i < h; i++){
            y = 1;
            for(u_char8 j = 0; j < w; j ++){
                pixel_color = get_pixel_color(data_img);
                data_img+=3;
                print_pixel(pixel_color, x, y);
                y++;
            }
            x--;
        }
        u_char8 exit[] = "1";
        input_no_format(exit, 1);
        set_video(3);
    }
}