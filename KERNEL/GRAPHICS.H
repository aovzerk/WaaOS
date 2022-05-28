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
void print_pixel(u_char8 pixel, u_int16 x, u_int16 y){
    asm volatile("pusha");
    asm volatile(
        "mov $0x0C, %%ah\n"
        "xor %%bx,%%bx\n"
        "mov %0, %%al\n"
        "int $0x10\n"
        :
        :"m"(pixel),"d"(y),"c"(x)
        :
    );
    asm volatile("popa");
}
void draw_image_bmp(u_char8 *image_bmp,u_int16 x_pos, u_int16 y_pos){
    u_char8 pixel_color = get_pixel_color(image_bmp);
    u_int16 w = image_bmp[18] + (image_bmp[17] << 8);
    u_int16 h = image_bmp[22] + (image_bmp[21] << 8);
    image_bmp += 138;
    u_int16 y = h + y_pos;
    u_int16 x = x_pos;
    for(u_int16 i = 0; i < h; i++){
        x = x_pos;
        for(u_int16 j = 0; j < w; j++){
            pixel_color = get_pixel_color(image_bmp);
            image_bmp+=3;
            print_pixel(pixel_color, x, y);
            x++;
        }
        y--;
    }
}
void get_res_image(u_char8 *data_file, u_int16 *w, u_int16 *h){
    w[0] = ((u_int16)data_file[19] << 8) + data_file[18];
    h[0] = ((u_int16)data_file[23] << 8) + data_file[22];
}