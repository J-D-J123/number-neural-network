/**
 * Author:          Joseph Johnson 
 * Date:            05/22/2026
 * File:            read_png.c 
 * Desc:            reads one png for the training to understand 
 *                      amount of pixels h (height) & w (width)
 */

// Simple PNG size reader (reads width and height from IHDR chunk)
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <windows.h>

// stb_image - v2.30 - public domain image loader
#define STB_IMAGE_IMPLEMENTATION
#include "../structs/stb_image.h"

#include "../structs/png.h"

/**
 * the get_png_info(...) func takes one param 
 * @param inputPNG is the input image inputed into the function, pretty simple :)
 * @returns the png structure of the data of the inputPNG, width, height, & num_of_pixels
 */
png get_png_info(const char * inputPNG) {

    // start as empty 
    png image = {0, 0, 0};

    int width, height, channels; 

    if (stbi_info(inputPNG, &width, &height, &channels)) {

        image.width = width; 
        image.height = height; 
        image.num_of_pixels = width * height;
    } else {

        printf("Error, failed to read image for %s\n", inputPNG);
    }

    return image; 
}

// pixels in color, one per element pixel array length * width aka 28 * 28 = 784 elements 
/**
 * the pixels_in_color_array(...) function takes two parameters
 * ONLY GIVES YOU ONE PIXEL ARRAY PER PNG
 * returns an array of pixels in RGB colors/ colours (however you say it)
 * @param int png* picture_size which has the height and width of the png 
 * @param char* inputPNG which is the "{input image}"
 */
PixelGrey* pixels_in_png_to_array(png* picture_size, const char* inputPNG) {

    int width, height, channels; 

    unsigned char * raw_pixels = stbi_load(inputPNG, &width, &height, &channels, 1); 

    if(!raw_pixels) {

        printf("Error enstaiting the raw_pixels array in pixels_in_2D_array)png * picture_size, const char * inputPNG for %s\n", inputPNG);
        return NULL; 
    }

    // make PixelGrey array to return 
    PixelGrey* pixels = malloc(picture_size->height * picture_size->width * sizeof(PixelGrey));    //  index via pixels[y * w + x] = (PixelGrey) {r, g, b}

    // PixelGrey array fails to malloc
    if (!pixels) {
        printf("Error making pixels array in pixels_in_png_to_2D_array(png * picture_size)\n");

        // free unused raw_pixels if pixels fails to malloc correctly
        stbi_image_free(raw_pixels); 
        return NULL; 
    }

    // loop through height then the width
    for (int y = 0; y < picture_size->height; y++) {
        for(int x = 0; x < picture_size->width; x++) {

            // get pixel color RGB color into the array 
            // https://stackoverflow.com/questions/4839623/getting-pixel-color-in-c

            // map the 2D grid (x, y) from x: width y: height to a 1D pixel index
            // int target_pixel_index = y * picture_size->width + x; 

            // map pixel index to byte index, each pixel is forced to have only 1 byte
            int current_byte_index = y * picture_size->width + x; ; 

            // read the channels out of the pointer array, just getting the values r,
            // values 0 - 255
            uint8_t grey = raw_pixels[current_byte_index];

            // divide by 255 so it is a true grey scale 
            grey = grey / 255; 

            // not picture_size->height * picture_size->width = 28 * 28 = 784 + 1 = 785 -> which is out of frame out of 
            // the png frame y * 28 + x = 0 through 783 aka 784 
            // pixels[y * picture_size->width + x] = (PixelGrey) {r, g, b};
            pixels[current_byte_index].grey = grey;

        }
    }

    // don't forget to release/ (free)
    stbi_image_free(raw_pixels); 

    return pixels; 

} 

// print values to see if it works 
void print_png_data(png image, PixelGrey * grey_array) {

    // png data
    printf("the image width is: %u and the height is: %u total pixels is: %u\n", image.width, image.height, image.num_of_pixels);
    
    printf("the greyscale data is as follows:\n");

    //RGB values data
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {

            // figure out correct index in rgb_array 
            int index = y * image.width + x; 

            // go through the array and print out each data item 
            printf("[%3u] ", grey_array[index].grey);
        }
        printf("\n");
    }
}