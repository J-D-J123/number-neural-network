/**
 * Author:          Joseph Johnson 
 * Date:            05/22/2026
 * File:            read_png.h
 * Desc:            requried packages in order to use for read_png.c 
 *                      to understand training png (pictures) 
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define SIZE 8; 

typedef unsigned char byte;

// functions 
static void get_pixel(const byte *image, unsigned int w, unsigned int h, 
                unsigned int x, unsigned int y); 

