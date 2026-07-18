/**
 * Author:          Joseph Johnson 
 * Date:            06/09/2026
 * File:            starts the neural network and sets it up from the first layer
 *                      then sends data through the network to determine what image it is
 */


#include <stdio.h> 
#include <stdlib.h> 

#include "../structs/png.h"

// first get each pixel and put it into a row & colummn and take each pixel and put into each neruon 
int main() {

    // read the png image first 28 * 28 pixels    
    png image = get_png_info("0_1.png");
    PixelGrey * pixels_greyscale = pixels_in_png_to_array(&image, "0_1.png"); 

    print_png_data(image, pixels_greyscale); 

    return 0;     
}