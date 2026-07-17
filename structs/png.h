#ifndef PNG_STRUCTS_H
#define PNG_STRUCTS_H

#include <stdint.h>

// picture data for each picture inputed into the network 
typedef struct _png {

    uint32_t width; 
    uint32_t height; 

    uint32_t num_of_pixels; 
} png; 

// Per pixel greyscale values [0-255] inclusive
typedef struct _PixelGrey {

    uint8_t grey; 

} PixelGrey; 

// ------------ FUNCTIONS -----------------
png get_png_info(const char * inputPNG);
PixelGrey* pixels_in_png_to_array(png* picture_size, const char* inputPNG);
void print_png_data(png image, PixelGrey * grey_array);

#endif