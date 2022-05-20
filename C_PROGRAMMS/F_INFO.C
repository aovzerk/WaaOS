

#include "BASE_LIB.H"

void main(void)
{   
    u_char8 fime_name[12];
    u_char8 file_data[512];
    print((u_char8 *)"Input file name => ", Light_Grey);
    
    input_no_format(fime_name, 12);
    daps daps_file = get_r_daps_file(fime_name, (u_int16) file_data);
    if(daps_file.p_empty == 1){
        print(new_line, Black);
        print((u_char8 *)"FILE NOT FOUND", Red);
        return;
    } else {
        f_string num_sectors = convert_to_string(daps_file.p_n_setors);
        f_string first_sector = convert_to_string(daps_file.sector);
        print(new_line, Black);
        print((u_char8 *) "File: ", Light_Grey);
        print_nl(fime_name, Light_Grey);
        print((u_char8 *) "Num. Sectors: ", Light_Grey);
        print_nl(num_sectors.data, Light_Grey);
        print((u_char8 *) "First Sector: ", Light_Grey);
        print_nl(first_sector.data, Light_Grey);
        if(daps_file.data_file.type == 1){
            print_nl((u_char8 *) "Type: execute", Red);
        } else if(daps_file.data_file.type == 2){
            load_daps(&daps_file);
            print_nl((u_char8 *) "Type: text", Green);
            print_nl((u_char8 *) "512 byte file:", Light_Grey);
            print_nl((u_char8 *) "=========================", Red);
            print(file_data, Light_Grey);
            print((u_char8 *) "\n\r=========================", Red);
        }
        
    }
}