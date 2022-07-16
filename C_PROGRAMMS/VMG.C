#include "LIB/BASE_LIB.H"
#include "LIB/GRAPHICS/VGA/VESA.H"
// #include "LIB/MEMORY.H"

void main(){
    // for (u_char8 i = 0; i < 255; i++)
    // {
        
    // }
    vbeInfoBlock info;
    info = vbeInfoGet();

    print((u_char8 *)"   signature | ", White);
    print_nl(info.signature, Light_Grey);

    print((u_char8 *)"     version | ", White);
    print_nl(convert_hex_to_str(info.version).data, Light_Grey);
    
    print((u_char8 *)"      memory | ", White);
    print((u_char8 *)(info.video_memory), Light_Grey);
    print_nl((u_char8 *)" KB", Light_Grey);

    print((u_char8 *)"capabilities | ", White);
    print_nl(convert_bin_to_str(info.capabilities).data, Light_Grey);
    
    print((u_char8 *)" video modes | ", White);
    print_nl(get_real_addres(info.video_modes), Light_Grey);
    // print_nl(convert_bin_to_str(info.capabilities).data, White);
    // asm("int $0x91\n");
}