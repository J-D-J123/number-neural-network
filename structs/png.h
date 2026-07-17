#ifndef PNG_STRUCTS_H
#define PNG_STRUCTS_H

#include <stdint.h>

// picture data for each picture inputed into the network 
typedef struct _png {

    uint32_t width; 
    uint32_t height; 

    uint32_t num_of_pixels; 
} png; 

// Per pixel RGB values 
typedef struct _PixelRGB {

    uint32_t r;
    uint32_t g; 
    uint32_t b; 

} PixelRGB; 


// ------------ FUNCTIONS -----------------
png get_png_info(const char * inputPNG);
PixelRGB* pixels_in_png_to_array(png* picture_size, const char* inputPNG);

#endif