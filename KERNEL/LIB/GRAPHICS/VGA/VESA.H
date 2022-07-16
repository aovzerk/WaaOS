#ifndef u_char8
#define u_char8 unsigned char
#define u_short16 unsigned short int
#define u_int32 unsigned long int
#define u_long_int64 unsigned long long int
#endif

struct of_seg
{
    u_short16 segment;
    u_short16 offset;
};

u_char8* get_real_addres(of_seg in){
    u_char8* out;
    asm volatile("pusha");
    asm volatile(""
        :"=a"(out)
        :"a"((u_int32)in.segment*16+in.offset)
        :
    );
    asm volatile("popa");
    return out;
};

struct vbeInfoBlock {
    u_char8 signature[4];       // must be "VESA" to indicate valid VBE support
	u_short16 version;            // VBE version; high byte is major version, low byte is minor version
	of_seg oem;                 // segment:offset pointer to OEM
	u_int32 capabilities;    // bitfield that describes card capabilities
	of_seg video_modes;         // segment:offset pointer to list of supported video modes
	u_short16 video_memory;       // amount of video memory in 64KB blocks
	u_short16 software_rev;       // software revision
	of_seg vendor;              // segment:offset to card vendor string
	of_seg product_name;        // segment:offset to card model name
	of_seg product_rev;         // segment:offset pointer to product revision
	u_char8 reserved[222];      // reserved for future expansion
	u_char8 oem_data[256];      // as # of 64KB blocks
};

struct vbe_mode_info_structure {
	u_short16 attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	u_char8 window_a;			// deprecated
	u_char8 window_b;			// deprecated
	u_short16 granularity;		// deprecated; used while calculating bank numbers
	u_short16 window_size;
	u_short16 segment_a;
	u_short16 segment_b;
	u_int32 win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	u_short16 pitch;			// number of bytes per horizontal line
	u_short16 width;			// width in pixels
	u_short16 height;			// height in pixels
	u_char8 w_char;			// unused...
	u_char8 y_char;			// ...
	u_char8 planes;
	u_char8 bpp;			// bits per pixel in this mode
	u_char8 banks;			// deprecated; total number of banks in this mode
	u_char8 memory_model;
	u_char8 bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	u_char8 image_pages;
	u_char8 reserved0;
 
	u_char8 red_mask;
	u_char8 red_position;
	u_char8 green_mask;
	u_char8 green_position;
	u_char8 blue_mask;
	u_char8 blue_position;
	u_char8 reserved_mask;
	u_char8 reserved_position;
	u_char8 direct_color_attributes;
 
	u_int32 framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	u_int32 off_screen_mem_off;
	u_short16 off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	u_char8 reserved1[206];
};

vbeInfoBlock vbeInfoGet(){
    vbeInfoBlock info;
    asm volatile("pusha");
    asm volatile(
        "mov $0x4f00, %%ax\n"
        "push %%cs\n"
        "pop %%es\n"
        "int $0x10\n"
        :
        :"D"(&info)
        :
    );
    asm volatile("popa");
    return info;
};