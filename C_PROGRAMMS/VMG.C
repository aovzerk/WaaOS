#include "LIB/BASE_LIB.H"
#include "LIB/GRAPHICS/GRAPHICS.H"
void main(void){
    // for (u_char8 i = 0; i < 255; i++)
    // {
        
    // }
    u_char8 mode = 0;
    mode = get_video_mode();
    print(convert_to_string((u_long_int64)mode).data, White);
}