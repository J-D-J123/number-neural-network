/**
 * Author:          Joseph Johnson 
 * Date:            06/09/2026
 * File:            starts the neural network and sets it up from the first layer
 *                      then sends data through the network to determine what image it is
 */


#include <stdio.h> 
#include <stdlib.h> 

#include "../structs/png.h"

void print_png_data(png image, PixelRGB * rgb_array); 

// first get each pixel and put it into a row & colummn and take each pixel and put into each neruon 
int main() {

    // read the png image first 28 * 28 pixels    
    png image = get_png_info("0_1.png");
    PixelRGB * rgb_array = pixels_in_png_to_array(&image, "0_1.png"); 

    print_png_data(image, rgb_array); 

    return 0;     
}

// print values to see if it works 
void print_png_data(png image, PixelRGB * rgb_array) {

    // png data
    printf("the image width is: %u and the height is: %u total pixels is: %u\n", image.width, image.height, image.num_of_pixels);
    
    printf("the RGB data is as follows:\n");

    //RGB values data
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {

            // figure out correct index in rgb_array 
            int index = y * image.width + x; 

            // go through the array and print out each data item 
            printf("[%3u, %3u, %3u] ", rgb_array[index].r, rgb_array[index].g, rgb_array[index].b);
        }
        printf("\n");
    }
}