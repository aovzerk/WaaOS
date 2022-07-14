#include "LIB/BASE_LIB.H"
#include "LIB/GRAPHICS/VGA/VESA.H"
// #include "LIB/MEMORY.H"

void main(){
    // for (u_char8 i = 0; i < 255; i++)
    // {
        
    // }
    vbeInfoBlock info;
    info = vbeInfoGet();
    // u_char8 name[5] = {info.vbeSignature[0],info.vbeSignature[1],info.vbeSignature[2],info.vbeSignature[3],0};
    print_nl(info.vbeSignature, White);
    print_nl(convert_to_string(info.vbeVersion).data, White);
    // asm("int $0x91\n");
}